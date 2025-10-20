#include "widget_config.h" 



void set_positioning(GtkWidget *widget, struct WidgetPositioning *pos){

  if(widget == NULL || pos == NULL) return;
  gtk_widget_set_halign(widget, pos->WIDGET_H_ALIGN);
  gtk_widget_set_valign(widget, pos->WIDGET_V_ALIGN);
  gtk_widget_set_hexpand(widget, pos->WIDGET_H_EXPAND);
  gtk_widget_set_vexpand(widget, pos->WIDGET_V_EXPAND);
  return;


}
