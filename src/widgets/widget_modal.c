#include "widget_modal.h" 




GtkWidget *new_modal(char *title, GtkWidget *view){
  
  GtkWidget *win = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(win), title);
  gtk_window_set_child(GTK_WINDOW(win), view);
  gtk_window_present(GTK_WINDOW(win));
  return win;

}

