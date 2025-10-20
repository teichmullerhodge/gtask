#ifndef WIDGET_TASK_LIST_H
#define WIDGET_TASK_LIST_H 

#include <gtk/gtk.h> 
struct Gtask {

  char *id;
  char *title;
  bool done;

};



void add_task(GtkWidget *task_list, const char *task_name);

GtkWidget *create_task_item(const char *task_name);
GtkWidget *tasks_list_new();


#endif 
