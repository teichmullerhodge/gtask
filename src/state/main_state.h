#ifndef MAIN_STATE_H
#define MAIN_STATE_H 


#include <gtk/gtk.h> 



void cursor_pointer(GtkEventControllerMotion *motion, double x, double y,
                    gpointer udata);
void cursor_default(GtkEventControllerMotion *motion, double x, double y,
                    gpointer udata);

void change_theme(GtkButton *theme_btn, gpointer user_data);


#endif 
