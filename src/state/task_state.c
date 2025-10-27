
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


