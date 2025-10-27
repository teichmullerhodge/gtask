#include "widget_state.h"

GtkEntryBuffer *get_entry_buff_from_widget(GtkWidget *widget){
    if(widget == NULL) return NULL;
    if(GTK_IS_ENTRY(widget)){
      return gtk_entry_get_buffer(GTK_ENTRY(widget));
    }
    for (GtkWidget *child = gtk_widget_get_first_child(widget);
     child != NULL;
     child = gtk_widget_get_next_sibling(child)) {
      bool inner_lookup = GTK_IS_BOX(child) || GTK_IS_SCROLLED_WINDOW(child) || GTK_IS_GRID(child);

      if(inner_lookup) {
        GtkEntryBuffer *buff = get_entry_buff_from_widget(child);
        if(buff != NULL) return buff;
      }


     if(GTK_IS_ENTRY(child)){
        return gtk_entry_get_buffer(GTK_ENTRY(child));
      }
    
    }
  
    printf("Nothing found at get_entry_buff_from_widget\n");

    return NULL;
}
GtkTextBuffer *get_text_buff_from_widget(GtkWidget *widget){

    if(widget == NULL) return NULL;
    if(GTK_IS_TEXT_VIEW(widget)){
      return gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
    }
    for (GtkWidget *child = gtk_widget_get_first_child(widget);
     child != NULL;
     child = gtk_widget_get_next_sibling(child)) {

      bool inner_lookup = GTK_IS_BOX(child) || GTK_IS_SCROLLED_WINDOW(child) || GTK_IS_GRID(child);

      if(inner_lookup) {
        GtkTextBuffer *buff = get_text_buff_from_widget(child);
        if(buff != NULL) return buff;
      }

     if(GTK_IS_TEXT_VIEW(child)){
        return gtk_text_view_get_buffer(GTK_TEXT_VIEW(child));
      }
    
    }
    printf("Nothing found at get_text_buff_from_widget\n");


    return NULL;


}
