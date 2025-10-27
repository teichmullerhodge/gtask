#ifndef TASK_LIST_STATE_H
#define TASK_LIST_STATE_H 

#include "../records/tasks.h"
#include <gtk/gtk.h> 

struct TaskListState {

  struct Gtask *task;
  GtkWidget *task_list;

};


#endif 
