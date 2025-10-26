#include "widget_task_list.h" 
#include "gtk/gtk.h"
#include "widget_touchable.h" 
#include "../helpers/file_helpers.h" 
#include "../appconfig/appconfig.h" 
#include "../records/tasks.h" 



void add_task(GtkWidget *task_list, uint64_t task_id, const char *task_name, const char *description, const char *created_at, const char *due_date){
    
  GtkWidget *item = create_task_item(task_id, task_name, description, created_at, due_date);
  gtk_list_box_append(GTK_LIST_BOX(task_list), item);
  gtk_widget_set_visible(item, true);


}
GtkWidget *create_task_item(uint64_t task_id, const char *name, const char *description, const char *created_at, const char *due_date) {
  (void)task_id;
  (void)created_at;
  (void)due_date;

  GtkWidget *box_task = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *box_labels = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

  gtk_widget_add_css_class(box_task, "task-container"); 
  GtkWidget *check_btn = gtk_check_button_new();

  GtkWidget *name_label = gtk_label_new(name);
  gtk_widget_add_css_class(name_label, "task-name-label");
  gtk_widget_set_halign(name_label, GTK_ALIGN_START);
  gtk_widget_set_valign(name_label, GTK_ALIGN_CENTER);  
  
  GtkWidget *description_label = gtk_label_new(description);
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
  GtkWidget *color_dialog_btn = gtk_color_dialog_button_new(color_dialog);
  GtkWidget *delete_btn = touchable(NULL, "user-trash-symbolic", "task-delete-btn");
  gtk_widget_set_tooltip_text(delete_btn, "Delete a task");
 

  gtk_box_append(GTK_BOX(box_labels), name_label);
  gtk_box_append(GTK_BOX(box_labels), description_label);

  gtk_box_append(GTK_BOX(box_task), check_btn);
  gtk_box_append(GTK_BOX(box_task), box_labels);


  gtk_box_append(GTK_BOX(box_task), color_dialog_btn);
  gtk_box_append(GTK_BOX(box_task), delete_btn);

  return box_task;


}

GtkWidget *tasks_list_new(){

  GtkWidget *scroll_win = gtk_scrolled_window_new();
  GtkWidget *tasks_list = gtk_list_box_new();
  gtk_widget_add_css_class(tasks_list, "tasks-list"); 
  
  GtkWidget *new_task = touchable("New task", "list-add-symbolic", "new-task-btn");
  gtk_list_box_append(GTK_LIST_BOX(tasks_list), new_task);
  char *home = getenv("HOME");
  char tasks_buff_path[2 << 8];

  snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);

  char *tasks_records = read_file_contents(tasks_buff_path);
  size_t tasks_count = 0;
  struct Gtask* tasks = parse_tasks(tasks_records, &tasks_count);  
  for(size_t k = 0; k < tasks_count; k++){
    
   add_task(tasks_list, tasks[k].id, tasks[k].title, tasks[k].description, tasks[k].created_at, tasks[k].due_date);
  }

  (void)tasks_records; 
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_win), tasks_list);
  return scroll_win;


}

