#include "widgets_form_entry.h"






GtkWidget *form_entry(const char *label, const char *contents, const char *css_class, bool editable){
  
  GtkWidget *entry = gtk_entry_new();
  printf("Form entry contents: %s\n", contents);

  if(contents != NULL){
    
    GtkEntryBuffer *buff = gtk_entry_get_buffer(GTK_ENTRY(entry));
    gtk_entry_buffer_set_text(buff, contents, strlen(contents));
  
  }
  
  gtk_widget_add_css_class(entry, css_class != NULL ? css_class : "form-entry");
  if(label == NULL) return entry;



  GtkWidget *label_widget = gtk_label_new(label);
  gtk_widget_add_css_class(label_widget, "form-label");

  gtk_widget_set_halign(label_widget, GTK_ALIGN_START);
  
  GtkWidget *entry_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_append(GTK_BOX(entry_box), label_widget);
  gtk_box_append(GTK_BOX(entry_box), entry);

  gtk_editable_set_editable(GTK_EDITABLE(entry), editable); 
  return entry_box;

}

GtkWidget *form_multiline_entry(const char *label, const char *contents, const char *css_class, bool editable){
 
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *scrolled_win = gtk_scrolled_window_new();
  GtkWidget *multiline_entry = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(multiline_entry), editable);


  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(multiline_entry), GTK_WRAP_WORD_CHAR);
  gtk_text_view_set_justification(GTK_TEXT_VIEW(multiline_entry), GTK_JUSTIFY_LEFT);


  if(contents != NULL){
    GtkTextBuffer *buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(multiline_entry));
    gtk_text_buffer_set_text(buff, contents, strlen(contents));
  
  }
  
  gtk_widget_add_css_class(main_box, css_class != NULL ? css_class : "form-multiline-main-box");
  gtk_widget_add_css_class(multiline_entry, "form-multiline-entry"); 
  gtk_widget_add_css_class(scrolled_win, "form-multiline-scroll-win");
  if(label == NULL) {
    gtk_widget_add_css_class(scrolled_win, css_class != NULL ? css_class : "form-multiline-entry");
    return scrolled_win;
  }
 


  GtkWidget *label_widget = gtk_label_new(label);
  gtk_widget_add_css_class(label_widget, "form-label");
  gtk_widget_set_halign(label_widget, GTK_ALIGN_START);
  


 

  gtk_widget_set_size_request(multiline_entry, 360, 120); 
  gtk_widget_set_hexpand(multiline_entry, TRUE);
  gtk_widget_set_vexpand(multiline_entry, TRUE);

  gtk_widget_set_hexpand(scrolled_win, TRUE);
  gtk_widget_set_vexpand(scrolled_win, TRUE);

  gtk_widget_set_size_request(scrolled_win, 360, 120); 

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_win), multiline_entry);
  
  gtk_box_append(GTK_BOX(main_box), label_widget);
  gtk_box_append(GTK_BOX(main_box), scrolled_win);

    return main_box;



}



GtkWidget *form_date_entry(const char *label, const char *date, const char *css_class, bool editable){
  (void)date;
  (void)editable;
  
  GtkWidget *label_widget = gtk_label_new(label != NULL ? label : "Calendar");
  gtk_widget_add_css_class(label_widget, "form-label");
  gtk_widget_set_halign(label_widget, GTK_ALIGN_START);
 
  GtkWidget *calendar = gtk_calendar_new();
  gtk_widget_add_css_class(calendar, css_class != NULL ? css_class : "form-calendar");



  if(date != NULL){
    int year, month, day; 
    if(sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
      perror("Failed to parse date.\n");
      return NULL;
    }

    printf("Date: %d-%d-%d\n", year, month, day);

    gtk_calendar_set_year(GTK_CALENDAR(calendar), year);
    gtk_calendar_set_month(GTK_CALENDAR(calendar), month - 1);
    gtk_calendar_set_day(GTK_CALENDAR(calendar), day);

  }

  GtkWidget *calendar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_append(GTK_BOX(calendar_box), label_widget);
  gtk_box_append(GTK_BOX(calendar_box), calendar);
  return calendar_box;



}




GtkWidget *form_switch(const char *label, bool is_on, const char *css_class){
  
  if(label == NULL) {
    perror("Label is required in form switch.\n");
    return NULL;
  }
  GtkWidget *label_widget = gtk_label_new(label);
  gtk_widget_add_css_class(label_widget, "form-label");
  gtk_widget_set_halign(label_widget, GTK_ALIGN_START);
  
  GtkWidget *switch_widget = gtk_switch_new();
  gtk_switch_set_active(GTK_SWITCH(switch_widget), is_on);


  gtk_widget_add_css_class(switch_widget, css_class != NULL ? css_class : "form-switch");
  GtkWidget *switch_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_append(GTK_BOX(switch_box), label_widget);
  gtk_box_append(GTK_BOX(switch_box), switch_widget);
  
  
  gtk_widget_set_halign(switch_box, GTK_ALIGN_START);
  return switch_box;
  


}

