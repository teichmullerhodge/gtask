#include "widget_touchable.h" 
#include "../state/state.h"


GtkWidget *touchable(const char *label, const char *icon, const char *cssclass){
  
  if(label == NULL && icon == NULL){
    perror("touchable: Either label or icon must be provided.");
    return NULL; 
  }
  
  GtkEventController *ctrl = gtk_event_controller_motion_new();
  GtkWidget *button = gtk_button_new();
  GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
  GtkWidget *label_widget = NULL;
  GtkWidget *icon_widget = NULL;
  if(icon != NULL) icon_widget = gtk_image_new_from_icon_name(icon);
  if(label != NULL) label_widget = gtk_label_new(label);
  if(icon_widget != NULL) gtk_box_append(GTK_BOX(hbox), icon_widget);
  if(label_widget != NULL) gtk_box_append(GTK_BOX(hbox), label_widget);
  gtk_button_set_child(GTK_BUTTON(button), hbox);
  
  gtk_widget_add_controller(button, ctrl);
  g_signal_connect(ctrl, "enter", G_CALLBACK(cursor_pointer), button);
  g_signal_connect(ctrl, "leave", G_CALLBACK(cursor_default), button);
  
  if(cssclass != NULL) gtk_widget_add_css_class(button, cssclass);
  return button;

}
