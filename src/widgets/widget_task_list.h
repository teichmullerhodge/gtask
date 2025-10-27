#ifndef WIDGET_TASK_LIST_H
#define WIDGET_TASK_LIST_H 

#include <gtk/gtk.h> 

#include "../records/tasks.h"

void add_task(GtkWidget *task_list, struct Gtask *task);

bool update_task_item(struct Gtask *task, GtkWidget *task_list); 
GtkWidget *create_task_item(struct Gtask* task, GtkWidget *task_list);

GtkWidget *tasks_list_new();


#endif 
