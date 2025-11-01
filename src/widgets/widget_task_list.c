#include "widget_task_list.h" 
#include "gdk/gdk.h"
#include "gtk/gtk.h"
#include "widget_task_dialog.h"
#include "widget_touchable.h" 
#include "../helpers/file_helpers.h" 
#include "../appconfig/appconfig.h" 
#include "../state/tag_state.h"
#include "../state/task_state.h"
#include "../state/task_list_state.h"
#include "../helpers/string_helpers.h"
#include "../helpers/color_helpers.h" 


void add_task(GtkWidget *task_list, struct Gtask *task){
  if(task == NULL) {
    perror("Task is null at add_task.\n");
    return;
  }  
  GtkWidget *item = create_task_item(task, task_list);
  gtk_list_box_append(GTK_LIST_BOX(task_list), item);
  gtk_widget_set_visible(item, true);


}


bool update_task_item(struct Gtask *task, GtkWidget *task_list) {
 (void)task;
 (void)task_list;
 return true;

}


GtkWidget *create_task_item(struct Gtask *task, GtkWidget *task_list) {
  
   if(task == NULL) {
    perror("Task is null at create_task_item.\n");
    return NULL;
  }  
  

  GtkWidget *box_task = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  char task_unique_name[2 << 8];
  snprintf(task_unique_name, sizeof(task_unique_name), "task_box_%ld_%s", task->id, task->created_at);
  sanitize_string(task_unique_name);

  gtk_widget_set_name(box_task, task_unique_name); 
  GtkWidget *edit_btn = touchable(NULL, "input-tablet-symbolic", "task-edit-btn");


  struct TaskListState *task_list_state = malloc(sizeof(struct TaskListState));
  if(task_list_state == NULL){
    perror("Malloc of task_list_stage failed at create_task_item.\n");
    return NULL;
  }

  task_list_state->task_list = task_list; 
  task_list_state->task = task;
  task_list_state->task_widget = box_task; 
  g_signal_connect(edit_btn, "clicked", G_CALLBACK(on_task_clicked), task_list_state);



  GtkWidget *box_labels = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

  gtk_widget_add_css_class(box_task, "task-container"); 
  GtkWidget *check_btn = gtk_check_button_new();
  
  gtk_check_button_set_active(GTK_CHECK_BUTTON(check_btn), task->done);

  GtkWidget *name_label = gtk_label_new(task->title);
  gtk_widget_add_css_class(name_label, "task-name-label");
  gtk_widget_set_halign(name_label, GTK_ALIGN_START);
  gtk_widget_set_valign(name_label, GTK_ALIGN_CENTER);  
  
  GtkWidget *description_label = gtk_label_new(task->description);
  gtk_widget_add_css_class(description_label, "task-description-label");
  gtk_widget_set_halign(description_label, GTK_ALIGN_START);
  gtk_widget_set_valign(description_label, GTK_ALIGN_CENTER);  

  gtk_label_set_ellipsize(GTK_LABEL(name_label), PANGO_ELLIPSIZE_END);
  gtk_label_set_single_line_mode(GTK_LABEL(name_label), TRUE);
  gtk_label_set_max_width_chars(GTK_LABEL(name_label), 20);

  gtk_label_set_ellipsize(GTK_LABEL(description_label), PANGO_ELLIPSIZE_END);
  gtk_label_set_single_line_mode(GTK_LABEL(description_label), TRUE);
  gtk_label_set_max_width_chars(GTK_LABEL(description_label), 40);

  gtk_widget_set_size_request(box_labels, 50, -1);
  gtk_widget_set_hexpand(box_labels, TRUE);

  GtkColorDialog *color_dialog = gtk_color_dialog_new();
  GtkWidget *tag_btn =  touchable(NULL, "tag-symbolic", "color-dialog-btn");   
  if(task->tag != NULL) gtk_widget_set_tooltip_text(tag_btn, task->tag->name); 
  
  char css_id_name[2 << 8];
  snprintf(css_id_name, sizeof(css_id_name), "tag_%ld_%s_%s", task->id, task->title, task->created_at);
 



  sanitize_string(css_id_name);
  gtk_widget_add_css_class(tag_btn, "tag-dialog-btn");
  gtk_widget_set_name(tag_btn, css_id_name);


  if(task->tag != NULL) {

    GdkRGBA *rgba_color = hex_to_gdkrgba(task->tag->color);
    set_tag_color(rgba_color, css_id_name);
  }


  struct TagDialogState* info = malloc(sizeof(struct TagDialogState));
  if(info == NULL) {
    perror("Malloc for TagDialogState failed.\n");
    return NULL;

  }

  info->dialog = color_dialog;
  info->tag_btn_css_id = strdup(css_id_name);

 
  g_signal_connect(tag_btn, "clicked", G_CALLBACK(on_tag_btn_clicked), info);

  GtkWidget *delete_btn = touchable(NULL, "user-trash-symbolic", "task-delete-btn");
  gtk_widget_set_tooltip_text(delete_btn, "Delete a task");
  
  
  g_signal_connect(delete_btn, "clicked", G_CALLBACK(on_delete_btn_clicked), task_list_state);
  g_signal_connect(check_btn, "toggled", G_CALLBACK(on_check_btn_clicked), task_list_state);
  gtk_box_append(GTK_BOX(box_labels), name_label);  
  gtk_box_append(GTK_BOX(box_labels), description_label);

  gtk_box_append(GTK_BOX(box_task), check_btn);
  gtk_box_append(GTK_BOX(box_task), box_labels);

  gtk_box_append(GTK_BOX(box_task), edit_btn); 
  gtk_box_append(GTK_BOX(box_task), tag_btn);
  gtk_box_append(GTK_BOX(box_task), delete_btn);

  gtk_widget_set_name(box_labels, "task_box_labels");
  gtk_widget_set_name(name_label, "task_title");
  gtk_widget_set_name(name_label, "task_description");
  gtk_widget_set_name(check_btn, "task_check");

  char box_id_name[2 << 9];
  snprintf(box_id_name, sizeof(box_id_name), "box_%ld", task->id);
  gtk_widget_set_name(GTK_WIDGET(box_task), box_id_name);
  return box_task;


}

GtkWidget *tasks_list_new(){

  GtkWidget *scroll_win = gtk_scrolled_window_new();
  GtkWidget *tasks_list = gtk_list_box_new();
  gtk_widget_add_css_class(tasks_list, "tasks-list"); 
  
  GtkWidget *new_task = touchable("New task", "list-add-symbolic", "new-task-btn");


  struct TaskListState *task_list_state = malloc(sizeof(struct TaskListState));
  if(task_list_state == NULL){
    perror("Malloc failed for task_list_state at task_list_new.\n");
    return NULL; 
  }

  task_list_state->task_list = tasks_list; 
  task_list_state->task = NULL; 
  g_signal_connect(new_task, "clicked", G_CALLBACK(open_task_dialog), task_list_state);
  
  gtk_list_box_append(GTK_LIST_BOX(tasks_list), new_task);
  char *home = getenv("HOME");
  char tasks_buff_path[2 << 8];


  snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);

  char *tasks_records = read_file_contents(tasks_buff_path);
  size_t tasks_count = 0;
  struct Gtask* tasks = parse_tasks(tasks_records, &tasks_count);  
  for(size_t k = 0; k < tasks_count; k++){
    
   add_task(tasks_list, &tasks[k]);
  }
  
  free(tasks_records);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_win), tasks_list);
  return scroll_win;


}

