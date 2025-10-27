#include "widget_task_dialog.h"
#include "widget_config.h"
#include "widget_touchable.h"
#include "widgets_form_entry.h"
#include "../appconfig/appconfig.h"
#include "../state/task_dialog_state.h"
#include "../state/task_list_state.h"
#include "../state/widget_state.h"
#include "../records/tasks.h"
#include "../helpers/color_helpers.h"
void open_task_dialog(GtkWidget *btn, gpointer user_data){
   
    (void)btn;
    struct TaskListState* task_list_state = (struct TaskListState*)user_data;
    if(task_list_state->task_list == NULL) {
      perror("Task list is null at open_task_dialog.\n");
      return;
    }
    bool new_task = task_list_state->task == NULL;


    struct Gtask *task = new_task ? new_default_task() : (struct Gtask*)task_list_state->task;
  
    struct TaskDialogState *task_dial_state = malloc(sizeof(struct TaskDialogState));
    if(task_dial_state == NULL) {
      perror("task_dial_state malloc failed.\n");
      return;
    }
    
    GtkWidget *task_win = gtk_window_new();
    

    gtk_window_present(GTK_WINDOW(task_win));
    gtk_window_set_title(GTK_WINDOW(task_win), new_task ? "Add a task" : task->title);
    
    gtk_window_set_default_size(GTK_WINDOW(task_win), APP_CONFIG_WIN_WIDTH / 1.4, APP_CONFIG_WIN_HEIGHT / 1.5);
    GtkWidget *task_grid = gtk_grid_new();

    GtkWidget *title_entry = form_entry("Title", task->title, NULL, true);
    GtkWidget *description_entry = form_multiline_entry("Description", task->description, NULL, true);
    
   
  
    GtkWidget *tag_name_label = gtk_label_new("Tag name");
    gtk_widget_add_css_class(tag_name_label, "form-label"); 
    gtk_widget_set_halign(tag_name_label, GTK_ALIGN_START);
  


    GtkWidget *tag_name_entry = gtk_entry_new();
    GtkEntryBuffer *buff = gtk_entry_get_buffer(GTK_ENTRY(tag_name_entry));

    if(task->tag != NULL){
      gtk_entry_buffer_set_text(buff, task->tag->name, strlen(task->tag->name));
    }

    GtkColorDialog *color_dialog = gtk_color_dialog_new();
    GtkWidget *color_dialog_btn = gtk_color_dialog_button_new(color_dialog);
    gtk_color_dialog_button_set_rgba(GTK_COLOR_DIALOG_BUTTON(color_dialog_btn), hex_to_gdkrgba(task->tag->color));

    GtkWidget *tag_info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *tag_entries_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    gtk_box_append(GTK_BOX(tag_entries_box), tag_name_entry);
    gtk_box_append(GTK_BOX(tag_entries_box), color_dialog_btn);

    gtk_box_append(GTK_BOX(tag_info_box), tag_name_label);
    gtk_box_append(GTK_BOX(tag_info_box), tag_entries_box);


    gtk_box_set_homogeneous(GTK_BOX(tag_entries_box), TRUE);


    gtk_widget_set_halign(color_dialog_btn, GTK_ALIGN_START);

    GtkWidget *save_btn = touchable(new_task ? "Save" : "Update task", "emblem-default-symbolic", "task-save-btn");
    GtkWidget *cancel_btn = touchable("Cancel", "dialog-error-symbolic", "task-cancel-btn");



    GtkWidget *box_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(box_buttons), cancel_btn);
    gtk_box_append(GTK_BOX(box_buttons), save_btn);
   
  
    gtk_box_set_homogeneous(GTK_BOX(box_buttons), TRUE);



    GtkWidget *created_at_entry = form_entry("Created at", task->created_at, NULL, false);
    GtkWidget *calendar_form = form_date_entry("Due date", task->due_date, NULL, true); 

    GtkWidget *done_switch = form_switch("Done", task->done, NULL);



    gtk_grid_attach(GTK_GRID(task_grid), title_entry, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(task_grid), description_entry, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(task_grid), tag_info_box, 0, 2, 1, 1);
    
  
    gtk_grid_attach(GTK_GRID(task_grid), created_at_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(task_grid), calendar_form, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(task_grid), done_switch, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(task_grid), box_buttons, 1, 3, 1, 1);
    


    gtk_grid_set_row_spacing(GTK_GRID(task_grid), 10); 
    gtk_grid_set_column_spacing(GTK_GRID(task_grid), 10); 
  


    set_positioning(task_grid, &(struct WidgetPositioning){
        GTK_ALIGN_FILL, 
        GTK_ALIGN_BASELINE_CENTER, 
        true, 
        true
    });

    task_dial_state->dialog_win = task_win;
    task_dial_state->task_list_widget = task_list_state->task_list; 
    task_dial_state->task_id = task->id;
    task_dial_state->title_buff = get_entry_buff_from_widget(title_entry);
    task_dial_state->created_at = task->created_at;
    task_dial_state->description_buff = get_text_buff_from_widget(description_entry);
    task_dial_state->tag_name_buff =  get_entry_buff_from_widget(tag_name_entry);
    task_dial_state->color_dialog_btn = color_dialog_btn;
    task_dial_state->switch_widget = gtk_widget_get_last_child(done_switch);
    task_dial_state->due_date_calendar_widget = gtk_widget_get_last_child(calendar_form);
    task_dial_state->is_new_task = new_task; 
    g_signal_connect(save_btn, "clicked", G_CALLBACK(save_task), task_dial_state);
    g_signal_connect(cancel_btn, "clicked", G_CALLBACK(dismiss_task), task_win);


    
    gtk_window_set_child(GTK_WINDOW(task_win), task_grid);
}
