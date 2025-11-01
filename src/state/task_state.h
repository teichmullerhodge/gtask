#ifndef TASK_STATE_H
#define TASK_STATE_H 

#include <gtk/gtk.h> 

void on_task_clicked(GtkButton *btn,
                         gpointer user_data);
void on_delete_btn_clicked(GtkButton *btn,
                         gpointer user_data);



void on_check_btn_clicked(GtkButton *btn, gpointer user_data);
#endif 
