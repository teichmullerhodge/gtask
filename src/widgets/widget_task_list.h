#ifndef WIDGET_TASK_LIST_H
#define WIDGET_TASK_LIST_H 

#include <gtk/gtk.h> 

void add_task(GtkWidget *task_list, uint64_t task_id, const char *task_name, const char *description, const char *created_at, const char *due_date);

GtkWidget *create_task_item(uint64_t task_id, const char *name, const char *description, const char *created_at, const char *due_date);

GtkWidget *tasks_list_new();


#endif 
