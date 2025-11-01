#include "task_dialog_state.h"
#include "../widgets/widget_task_list.h"
#include "../helpers/color_helpers.h"
#include <string.h>
#include "../records/tags.h"
#include "../records/tasks.h"
#include "task_list_state.h"


void dismiss_task(GtkWidget *btn, gpointer user_data){

  (void)btn;
  GtkWidget *win = GTK_WIDGET(user_data);
  gtk_window_destroy(GTK_WINDOW(win));
  return;

}

bool save_task(GtkWidget *btn, gpointer user_data){
    
  (void)btn;
  struct TaskDialogState* task_state = (struct TaskDialogState*)user_data;
  const char *title = gtk_entry_buffer_get_text(task_state->title_buff);
  
  GtkTextIter desc_start, desc_end;
  gtk_text_buffer_get_start_iter(task_state->description_buff, &desc_start);
  gtk_text_buffer_get_end_iter(task_state->description_buff, &desc_end);
  
  char *desc = gtk_text_buffer_get_text(task_state->description_buff, &desc_start, &desc_end, false);

  if(strlen(title) == 0 || strlen(desc) == 0) {
    perror("Title and description are required.\n");
    return false;
  }


  struct Gtask *task = malloc(sizeof(struct Gtask));
  if(task == NULL) {
  
    perror("task malloc failed at save_task.\n");
    return false;
    
  }
  
  const char *tag_name = gtk_entry_buffer_get_text(task_state->tag_name_buff);
  
  const GdkRGBA *color =  gtk_color_dialog_button_get_rgba(GTK_COLOR_DIALOG_BUTTON(task_state->color_dialog_btn));

  bool done = gtk_switch_get_active(GTK_SWITCH(task_state->switch_widget));

  int32_t day = gtk_calendar_get_day(GTK_CALENDAR(task_state->due_date_calendar_widget));
  int32_t month = gtk_calendar_get_month(GTK_CALENDAR(task_state->due_date_calendar_widget)) + 1;
  int32_t year = gtk_calendar_get_year(GTK_CALENDAR(task_state->due_date_calendar_widget));


  char formatted_day[2 << 2];
  char formatted_month[ 2 << 2];
  snprintf(formatted_day, sizeof(formatted_day), day < 10 ? "0%d" : "%d", day);
  snprintf(formatted_month, sizeof(formatted_month), month < 10 ? "0%d" : "%d", month);

  struct Gtag *tag = malloc(sizeof(struct Gtag));
  if(tag == NULL) {
    perror("Tag malloc failed at save_task.\n");
    return false;

  }

  snprintf(tag->name, sizeof(tag->name), "%s", tag_name);
  snprintf(tag->color, sizeof(tag->color), "%s", gdkrgba_to_hex(color));




  task->id = task_state->task_id;
  task->done = done;
  snprintf(task->title, sizeof(task->title), "%s", title);
  task->description = desc;
  task->project_id = 0;

  snprintf(task->created_at, sizeof(task->created_at), "%s", task_state->created_at);  
  snprintf(task->due_date, sizeof(task->due_date), "%d-%s-%s 00:00", year, formatted_month, formatted_day);
  task->priority = TASK_PRIORITY_UNKNOW;
  task->tag = tag; 


  if(!task_state->is_new_task) {
  
    bool updated = update_task(task);
    if(updated) {
      // refresh the ui state to reflect the changes. 
      bool refreshed = refresh_task(task_state->task_list_widget, task, task_state->task_list_state);
      if(refreshed) printf("Task updated.\n");
    }

    gtk_window_destroy(GTK_WINDOW(task_state->dialog_win));
    return updated; 


  }

  bool task_saved = record_new_task(task);
  gtk_window_destroy(GTK_WINDOW(task_state->dialog_win));
  
  GtkWidget *item = create_task_item(task, task_state->task_list_widget);
  gtk_list_box_append(GTK_LIST_BOX(task_state->task_list_widget), item);
  gtk_widget_set_visible(item, true);


  return task_saved;
  

}
