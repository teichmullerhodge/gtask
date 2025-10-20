
#include "home_page.h"
#include "../widgets/widget_task_list.h" 
#include "../layout/layout.h" 


GtkWidget *view_home_page(){

  GtkWidget *grid = gtk_grid_new();
  gtk_widget_add_css_class(grid, "home-page-grid");
  gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 20);

  gtk_widget_set_margin_start(grid, 20);
  gtk_widget_set_margin_bottom(grid, 20);
  gtk_widget_set_margin_end(grid, 20);
  gtk_widget_set_margin_top(grid, 10);

  GtkWidget *search_box = gtk_search_entry_new();
  gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_box), "Search...");
 
  GtkWidget *greetings_label = gtk_label_new("Welcome to Gtask");
  GtkWidget *calendar = gtk_calendar_new();
  
  GtkWidget *tasks_label = gtk_label_new("Your tasks");
  GtkWidget *tasks_list = tasks_list_new();
  gtk_grid_attach(GTK_GRID(grid), search_box, 0, 0, 2, 1);
  gtk_grid_attach(GTK_GRID(grid), greetings_label, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), tasks_label, 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), calendar, 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), tasks_list, 1, 2, 1, 1);
  
  expand_all(tasks_list);
  expand_all(calendar);
  

  gtk_widget_set_hexpand(search_box, TRUE);
  gtk_widget_set_vexpand(search_box, FALSE);
  gtk_widget_set_halign(search_box, GTK_ALIGN_FILL);

  return grid;

}
