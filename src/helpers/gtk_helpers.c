#include "gtk_helpers.h"



bool gtk_helpers_list_box_append_many(GtkWidget* list_box, GtkWidget **widgets, size_t len){

  if(list_box == NULL) {
    perror("list_box is null at gtk_helpers_list_box_append_many");
    return false; 
  }

  for(size_t k = 0; k < len; k++) {
    gtk_list_box_append(GTK_LIST_BOX(list_box), widgets[k]);
  }

  return true;


}
