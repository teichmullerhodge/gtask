#ifndef GTK_HELPERS_H
#define GTK_HELPERS_H 




#include <stdbool.h>
#include <gtk/gtk.h> 

bool gtk_helpers_list_box_append_many(GtkWidget* list_box, GtkWidget **widgets, size_t len);




#endif 
