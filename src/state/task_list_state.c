
#include "task_list_state.h"
#include "../helpers/string_helpers.h"
#include "../helpers/color_helpers.h" 

bool refresh_task(GtkWidget *task_list, struct Gtask *task, struct TaskListState *current_list_state){

  printf("In refresh_task.\n");
  if(task == NULL || task_list == NULL || current_list_state == NULL) return false;
  char task_unique_name[2 << 8];
  snprintf(task_unique_name, sizeof(task_unique_name), "box_%ld", task->id);
  sanitize_string(task_unique_name);

  printf("Task unique name: %s\n", task_unique_name);

  GtkWidget *child = gtk_widget_get_first_child(task_list)  ;
  while(child != NULL) {
    GtkWidget *box = gtk_list_box_row_get_child(GTK_LIST_BOX_ROW(child));
    printf("Child at refresh_task name: %s\n", gtk_widget_get_name(box));
    if(strcmp(task_unique_name, gtk_widget_get_name(box)) == 0){
      printf("Task found: %s\n", gtk_widget_get_name(box));
      return update_task_widget(child, task, current_list_state);       
    }

    child = gtk_widget_get_next_sibling(child);
  }

  return false;
}


bool update_task_widget(GtkWidget *taskrow, struct Gtask* task, struct TaskListState *current_list_state){

  (void)task;
  GtkWidget *box = gtk_widget_get_first_child(taskrow);
  if(!GTK_IS_BOX(box) || current_list_state == NULL) return false;


  GtkWidget *child = gtk_widget_get_first_child(box);
  GtkWidget *task_box_labels = NULL;
  GtkWidget *tag_btn = NULL;
  GtkWidget *check_btn = NULL;
  char *tag_name = NULL;
  printf("Entering in the child loop...\n");
  while(child != NULL){
  
    printf("Widget names: %s\n", gtk_widget_get_name(child));
    printf("Looking for widget: %s\n", gtk_widget_get_name(child));
    if(tag_btn != NULL && task_box_labels != NULL && check_btn != NULL) { 
      break; 
    } 

    if(strcmp("task_box_labels", gtk_widget_get_name(child)) == 0){
      task_box_labels = child;
    }

    if(strcmp("task_check", gtk_widget_get_name(child)) == 0){
      check_btn = child;
    }

    if(strstr(gtk_widget_get_name(child), "tag_") != NULL) {
      tag_btn = child;
      tag_name = strdup(gtk_widget_get_name(child));
    }
    
    child = gtk_widget_get_next_sibling(child);
  }


  bool widgets_found = tag_btn != NULL && task_box_labels != NULL && check_btn != NULL;
  if(widgets_found) {

    printf("Updating...\n");
    GdkRGBA *rgba_color = hex_to_gdkrgba(task->tag->color);
    set_tag_color(rgba_color, tag_name);
    gtk_widget_set_tooltip_text(tag_btn, task->tag->name);

    GtkWidget* name_label = gtk_widget_get_first_child(task_box_labels);
    GtkWidget* description_label = gtk_widget_get_last_child(task_box_labels);
    gtk_label_set_text(GTK_LABEL(name_label), task->title);
    gtk_label_set_text(GTK_LABEL(description_label), task->description);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_btn), task->done);
    current_list_state->task = task;
    
  }

  if(tag_name != NULL) free(tag_name);
  return widgets_found;
 

}

