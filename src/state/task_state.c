
#include "task_state.h" 
#include "../records/tasks.h"
#include "../widgets/widget_task_dialog.h"
#include "task_list_state.h"

void on_task_clicked(GtkButton *btn,
                         gpointer user_data){

    (void)btn;

    struct TaskListState* task_list_state = (struct TaskListState*)user_data;
    
    printf("Created_at: %s\n", task_list_state->task->created_at);
    open_task_dialog(GTK_WIDGET(btn), task_list_state);

}

void on_delete_btn_clicked(GtkButton *btn, gpointer user_data) {
    (void)btn;
    struct TaskListState *task_list_state = (struct TaskListState*)user_data;
    if (!task_list_state || !task_list_state->task) return;



    GtkListBox *list_box = GTK_LIST_BOX(task_list_state->task_list);
    char box_id_name[512];
    snprintf(box_id_name, sizeof(box_id_name), "box_%lu", task_list_state->task->id);

    GtkWidget *row = gtk_widget_get_first_child(GTK_WIDGET(list_box));
    while (row) {
        GtkWidget *next_row = gtk_widget_get_next_sibling(row);
        GtkWidget *child = gtk_widget_get_first_child(row);
        while (child) {
            if (strcmp(gtk_widget_get_name(child), box_id_name) == 0 && remove_task(task_list_state->task->id)) {
              
               gtk_list_box_remove(list_box, row);
               return;
            }

            child = gtk_widget_get_next_sibling(child);
        }

        row = next_row;
    }

    printf("Nothing found..\n");
}

void on_check_btn_clicked(GtkButton *btn, gpointer user_data){

    (void)btn;
    struct TaskListState *task_list_state = (struct TaskListState*)user_data;
    if (!task_list_state || !task_list_state->task) return;
    task_list_state->task->done = !task_list_state->task->done;
    if(refresh_task(task_list_state->task_list, task_list_state->task, task_list_state)){
      update_task(task_list_state->task);
    }

}
