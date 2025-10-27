#ifndef WIDGETS_FORM_ENTRY_H 
#define WIDGETS_FORM_ENTRY_H 

#include <gtk/gtk.h> 

GtkWidget *form_entry(const char *label, const char *contents, const char *css_class, bool editable);

GtkWidget *form_multiline_entry(const char *label, const char *contents, const char *css_class, bool editable);

GtkWidget *form_date_entry(const char *label, const char *date, const char *css_class, bool editable);

GtkWidget *form_switch(const char *label, bool is_on, const char *css_class);


#endif 
