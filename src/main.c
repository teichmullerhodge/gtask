#include "appconfig/appconfig.h"
#include "widgets/widget_touchable.h" 
#include "state/state.h" 
#include "widgets/widget_config.h" 
#include "records/tasks.h" 
#include "pages/home_page.h" 
#include "layout/layout.h" 
#include <gtk/gtk.h>


static GtkWidget *stack; 


static void switch_page(GtkWidget *widget, gpointer user_data) {
  (void)widget;
  const char *page_name = user_data;
  if(page_name == NULL || stack == NULL) return;
  printf("Switching to page -> %s\n", page_name);
  gtk_stack_set_visible_child_name(GTK_STACK(stack), page_name);

}
static void on_activate(GtkApplication *app) {
  
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "./resources/css/index.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);

  g_object_unref(provider);

  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), APP_CONFIG_WIN_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), APP_CONFIG_WIN_WIDTH, APP_CONFIG_WIN_HEIGHT);
  gtk_widget_add_css_class(window, "window-main");
 

  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  

  GtkWidget *sidebar = gtk_list_box_new();
  gtk_widget_add_css_class(GTK_WIDGET(sidebar), "sidebar");
  gtk_list_box_set_selection_mode(GTK_LIST_BOX(sidebar), GTK_SELECTION_NONE);

  GtkWidget *home_btn = touchable("Home", "view-grid-symbolic", "sidebar-btn");
  GtkWidget *tasks_btn = touchable("Tasks", "x-office-calendar-symbolic", "sidebar-btn");
  GtkWidget *projects_btn = touchable("Projects", "send-to-symbolic", "sidebar-btn");
  GtkWidget *configs_btn = touchable("Configurations", "emblem-system-symbolic", "sidebar-btn");

  g_signal_connect(home_btn,    "clicked", G_CALLBACK(switch_page), "home");
  g_signal_connect(tasks_btn,   "clicked", G_CALLBACK(switch_page), "tasks");
  g_signal_connect(projects_btn,"clicked", G_CALLBACK(switch_page), "projects");
  g_signal_connect(configs_btn, "clicked", G_CALLBACK(switch_page), "config");

  
  GtkWidget *change_theme_btn = touchable(NULL, "weather-clear-symbolic", "change-theme-btn");
  gtk_widget_set_name(change_theme_btn, "clear");
  g_signal_connect(change_theme_btn, "clicked", G_CALLBACK(change_theme), NULL);

  
  gtk_widget_set_valign(GTK_WIDGET(change_theme_btn), GTK_ALIGN_BASELINE_CENTER);
  gtk_widget_set_halign(GTK_WIDGET(change_theme_btn), GTK_ALIGN_BASELINE_CENTER);
 
  gtk_widget_set_vexpand(GTK_WIDGET(change_theme_btn), false);
  gtk_widget_set_hexpand(GTK_WIDGET(change_theme_btn), false); 

  gtk_widget_set_size_request(GTK_WIDGET(change_theme_btn), 10, 10);

  gtk_list_box_append(GTK_LIST_BOX(sidebar), home_btn); 
  gtk_list_box_append(GTK_LIST_BOX(sidebar), tasks_btn); 
  gtk_list_box_append(GTK_LIST_BOX(sidebar), projects_btn); 
  gtk_list_box_append(GTK_LIST_BOX(sidebar), configs_btn); 
  gtk_list_box_append(GTK_LIST_BOX(sidebar), change_theme_btn);

  stack = gtk_stack_new();
  gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
  gtk_stack_set_transition_duration(GTK_STACK(stack), 250);
  gtk_widget_add_css_class(GTK_WIDGET(stack), "main-stack");


  GtkWidget *home_page = view_home_page();  


                                             
                                           
  GtkWidget *tasks_page = gtk_label_new("📅 Tasks Page");
  GtkWidget *projects_page = gtk_label_new("📂 Projects Page");
  GtkWidget *config_page = gtk_label_new("⚙️ Configurations Page");
  
  set_positioning(home_page, &(struct WidgetPositioning){
      .WIDGET_V_ALIGN = GTK_ALIGN_START,
      .WIDGET_H_ALIGN = GTK_ALIGN_START,
      .WIDGET_V_EXPAND = false,
      .WIDGET_H_EXPAND = false 
  });
  set_positioning(tasks_page, &(struct WidgetPositioning){
      .WIDGET_V_ALIGN = GTK_ALIGN_START,
      .WIDGET_H_ALIGN = GTK_ALIGN_START,
      .WIDGET_V_EXPAND = false,
      .WIDGET_H_EXPAND = false 
  });
  set_positioning(projects_page, &(struct WidgetPositioning){
      .WIDGET_V_ALIGN = GTK_ALIGN_START,
      .WIDGET_H_ALIGN = GTK_ALIGN_START,
      .WIDGET_V_EXPAND = false,
      .WIDGET_H_EXPAND = false 
  });


  set_positioning(config_page, &(struct WidgetPositioning){
      .WIDGET_V_ALIGN = GTK_ALIGN_START,
      .WIDGET_H_ALIGN = GTK_ALIGN_START,
      .WIDGET_V_EXPAND = false,
      .WIDGET_H_EXPAND = false 
  });


  gtk_stack_add_named(GTK_STACK(stack), home_page, "home");
  gtk_stack_add_named(GTK_STACK(stack), tasks_page, "tasks");
  gtk_stack_add_named(GTK_STACK(stack), projects_page, "projects");
  gtk_stack_add_named(GTK_STACK(stack), config_page, "config");

  gtk_box_append(GTK_BOX(main_box), sidebar);
  gtk_box_append(GTK_BOX(main_box), stack);

  expand_all(main_box);
  expand_all(stack);


  gtk_widget_set_halign(GTK_WIDGET(home_page), GTK_ALIGN_FILL);

  gtk_window_set_child(GTK_WINDOW(window), main_box);  
  
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {

  GtkApplication *app =
      gtk_application_new(APP_CONFIG_APP_ID, APP_CONFIG_APP_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
