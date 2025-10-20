#include "state.h"

void cursor_pointer(GtkEventControllerMotion *motion, double x, double y,
                    gpointer udata){
(void)motion;
(void)x;
(void)y;
GtkWidget *widget = GTK_WIDGET(udata);
gtk_widget_set_cursor_from_name(widget, "pointer");

}
void cursor_default(GtkEventControllerMotion *motion, double x, double y,
                    gpointer udata){

(void)motion;
(void)x;
(void)y;
GtkWidget *widget = GTK_WIDGET(udata);
gtk_widget_set_cursor_from_name(widget, NULL);


}

void change_theme(GtkButton *theme_btn, gpointer user_data){
  
  (void)user_data;
  if(theme_btn == NULL) {
    perror("change_theme: theme_btn is null.");
    return;
  }
  const char *current_name = gtk_widget_get_name(GTK_WIDGET(theme_btn));
  if(current_name == NULL) {
    perror("change_theme: Current icon is null.");
    return;

  }
  if(strcmp(current_name, "clear") == 0) {
    gtk_button_set_icon_name(GTK_BUTTON(theme_btn), "weather-clear-night-symbolic");
    gtk_widget_set_name(GTK_WIDGET(theme_btn), "dark");
    return;
  }
  if(strcmp(current_name, "dark") == 0) {
    gtk_button_set_icon_name(GTK_BUTTON(theme_btn), "weather-clear-symbolic");
    gtk_widget_set_name(GTK_WIDGET(theme_btn), "clear");
    return; 
  } 

}
