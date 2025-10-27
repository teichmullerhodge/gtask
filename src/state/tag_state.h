#ifndef TAG_STATE_H
#define TAG_STATE_H 



#include <gtk/gtk.h>



struct TagDialogState {


  GtkColorDialog* dialog;
  char *tag_btn_css_id;

};


void on_tag_btn_clicked(GtkButton *btn, gpointer user_data);
void on_color_chosen(GtkColorDialog *dialog, GAsyncResult *res, gpointer user_data);



#endif 
