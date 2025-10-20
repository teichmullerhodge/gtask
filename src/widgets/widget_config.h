#ifndef WIDGET_CONFIG_H
#define WIDGET_CONFIG_H 

#include <gtk/gtk.h>
#include <stdbool.h> 

struct WidgetPositioning {
  
  int WIDGET_V_ALIGN;
  int WIDGET_H_ALIGN;
  bool WIDGET_H_EXPAND;
  bool WIDGET_V_EXPAND;

};


void set_positioning(GtkWidget *widget, struct WidgetPositioning* pos);


#endif 
