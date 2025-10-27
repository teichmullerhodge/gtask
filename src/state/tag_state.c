
#include "tag_state.h" 


void on_tag_btn_clicked(GtkButton *btn, gpointer user_data) {
    struct TagDialogState* info = (struct TagDialogState*)user_data;
    if(info == NULL) return;
  
    if(info->dialog == NULL) {
      perror("Dialog is null at tab_btn_clicked.\n");
      return;
    }
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(btn)));
    gtk_color_dialog_choose_rgba(info->dialog, parent, NULL, NULL,
        (GAsyncReadyCallback)on_color_chosen, info->tag_btn_css_id);


}

void on_color_chosen(GtkColorDialog *dialog, GAsyncResult *res, gpointer user_data) {
    (void)user_data; 
    GError *error = NULL;
    GdkRGBA *color = gtk_color_dialog_choose_rgba_finish(dialog, res, &error);
    if (color == NULL) {
        if (error) {
            g_warning("Error chosing color: %s", error->message);
            g_error_free(error);
        }
        return;
    }

    g_print("Color: rgba(%g, %g, %g, %g)\n", color->red, color->green, color->blue, color->alpha);
  
  const char *tag_css_id = (char*)user_data;
  char css_icon[2 << 10];
  snprintf(css_icon, sizeof(css_icon),
         "#%s image { color: rgba(%d,%d,%d,%g); }",
         tag_css_id,
         (int)(color->red*255),
         (int)(color->green*255),
         (int)(color->blue*255),
         color->alpha);

  char css_bg[2 << 10];
  snprintf(css_bg, sizeof(css_bg),
         "#%s { background-color: rgba(%d,%d,%d, 0.1); }",
         tag_css_id,
         (int)(color->red*255),
         (int)(color->green*255),
         (int)(color->blue*255)); 

  GtkCssProvider *color_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_string(color_provider, css_icon);

  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(color_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);
  
  GtkCssProvider *bg_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_string(bg_provider, css_bg);

  printf("Css: %s\n", css_bg);
  printf("Css: %s\n", css_icon);

  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(bg_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  
  g_object_unref(color_provider);
  g_object_unref(bg_provider);
  gdk_rgba_free(color);
  

}

