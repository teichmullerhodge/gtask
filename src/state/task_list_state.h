#ifndef TASK_LIST_STATE_H
#define TASK_LIST_STATE_H 

#include "../records/tasks.h"
#include <gtk/gtk.h> 
#include <stdint.h>

struct TaskListState {

  struct Gtask *task;
  GtkWidget *task_list;
  GtkWidget *task_widget;
};

bool refresh_task(GtkWidget *task_list, struct Gtask *task, struct TaskListState *current_list_state);
bool update_task_widget(GtkWidget *taskrow, struct Gtask* task, struct TaskListState *current_list_state); 



#endif 
