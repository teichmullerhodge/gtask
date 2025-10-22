#include "widget_task_list.h" 
#include "gtk/gtk.h"
#include "widget_touchable.h" 
#include "../helpers/file_helpers.h" 
#include "../appconfig/appconfig.h" 


void add_task(GtkWidget *task_list, const char *task_name){
  
  GtkWidget *item = create_task_item(task_name);
  gtk_list_box_append(GTK_LIST_BOX(task_list), item);
  gtk_widget_set_visible(item, true);


}
GtkWidget *create_task_item(const char *task_name) {

  GtkWidget *box_task = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_widget_add_css_class(box_task, "task-container"); 
  GtkWidget *check_btn = gtk_check_button_new();

  GtkWidget *label = gtk_editable_label_new(task_name);
  gtk_widget_add_css_class(label, "task-label");
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(label, GTK_ALIGN_CENTER);  
  
  GtkColorDialog *color_dialog = gtk_color_dialog_new();
  GtkWidget *color_dialog_btn = gtk_color_dialog_button_new(color_dialog);
  GtkWidget *delete_btn = touchable(NULL, "user-trash-symbolic", "task-delete-btn");
  gtk_widget_set_tooltip_text(delete_btn, "Delete a task");
 

  gtk_box_append(GTK_BOX(box_task), check_btn);
  gtk_box_append(GTK_BOX(box_task), label);


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

  printf("tasks path: %s\n", tasks_buff_path);
  char *tasks_records = read_file_contents(tasks_buff_path);
  for(size_t k = 0; k < 15; k++){
   add_task(tasks_list, "Enviar relatório");
  }

  (void)tasks_records; 
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_win), tasks_list);
  return scroll_win;


}

