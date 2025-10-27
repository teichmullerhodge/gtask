#ifndef TASK_DIALOG_STATE_H
#define TASK_DIALOG_STATE_H 

#include <gtk/gtk.h>

struct TaskDialogState {



  GtkWidget *dialog_win;
  GtkWidget *task_list_widget;
  uint64_t task_id;
  GtkEntryBuffer *title_buff;
  const char *created_at;
  GtkTextBuffer *description_buff;
  GtkEntryBuffer *tag_name_buff;
  GtkWidget *color_dialog_btn;
  GtkWidget *switch_widget;
  GtkWidget *due_date_calendar_widget;
  bool is_new_task;

};


bool save_task(GtkWidget *btn, gpointer user_data);
void dismiss_task(GtkWidget *btn, gpointer user_data);

#endif 
