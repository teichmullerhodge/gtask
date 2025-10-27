#ifndef WIDGET_STATE_H
#define WIDGET_STATE_H 


#include <gtk/gtk.h> 



GtkEntryBuffer *get_entry_buff_from_widget(GtkWidget *widget);
GtkTextBuffer *get_text_buff_from_widget(GtkWidget *widget);


#endif 
