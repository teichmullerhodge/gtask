#include "color_helpers.h" 
#include <math.h>



char *gdkrgba_to_hex(const GdkRGBA *const rgba) {
    guchar red = roundf(rgba->red * 255.0f);
    guchar green = roundf(rgba->green * 255.0f);
    guchar blue = roundf(rgba->blue * 255.0f);

    char *to = malloc(RGB_HEX_STRING_LENGTH);
    if (!to) {
      perror("malloc failed at gdkrgba_to_hex.\n");
      return NULL; 
    }

    snprintf(to, RGB_HEX_STRING_LENGTH, "#%02hhx%02hhx%02hhx", red, green, blue);

    return to;
}



GdkRGBA *hex_to_gdkrgba(const char *hex_color) {
    if (!hex_color) return NULL;

    if (hex_color[0] == '#') hex_color++;

    size_t len = strlen(hex_color);
    if (len != 6 && len != 8) { // RRGGBB ou RRGGBBAA
        perror("Invalid hex color length");
        return NULL;
    }

    uint32_t r, g, b, a = 255;
    if (len == 6) {
        if (sscanf(hex_color, "%02x%02x%02x", &r, &g, &b) != 3) return NULL;
    } else {
        if (sscanf(hex_color, "%02x%02x%02x%02x", &r, &g, &b, &a) != 4) return NULL;
    }

    GdkRGBA *color = malloc(sizeof(GdkRGBA));
    if (!color) return NULL;

    color->red   = r / 255.0;
    color->green = g / 255.0;
    color->blue  = b / 255.0;
    color->alpha = a / 255.0;

    return color;
}


bool set_tag_color(GdkRGBA *color, const char *tag_css_id){


  if(color == NULL) {
    perror("Color is null at set_tag_color.\n");
    return false;
  }
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

  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(bg_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);


  g_object_unref(color_provider);
  g_object_unref(bg_provider);
  gdk_rgba_free(color);
 

  return true; 
}
