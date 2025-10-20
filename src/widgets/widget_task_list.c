#include "widget_task_list.h" 
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
  GtkWidget *label = gtk_label_new(task_name);
  gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(label, GTK_ALIGN_CENTER);

  GtkWidget *done_btn = touchable(NULL, "object-select-symbolic", "done-btn");
  gtk_widget_set_tooltip_text(done_btn, "Mark as done");
  gtk_box_append(GTK_BOX(box_task), label);
  gtk_box_append(GTK_BOX(box_task), done_btn);

  return box_task;


}

GtkWidget *tasks_list_new(){

  GtkWidget *scroll_win = gtk_scrolled_window_new();
  GtkWidget *tasks_list = gtk_list_box_new();
  
  char *home = getenv("HOME");
  char tasks_buff_path[2 << 8];

  snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);

  printf("tasks path: %s\n", tasks_buff_path);
  char *tasks_records = read_file_contents(tasks_buff_path);
  for(size_t k = 0; k < 15; k++){
   add_task(tasks_list, "Enviar relatório");
  }

  printf("Contents of record: %s\n", tasks_records);
 
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_win), tasks_list);
  return scroll_win;


}

