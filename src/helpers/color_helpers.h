#ifndef COLOR_HELPERS_H
#define COLOR_HELPERS_H 


#include <gtk/gtk.h> 
#include <stdbool.h> 
#define RGB_HEX_STRING_LENGTH 8 // #RRGGBB\0

char *gdkrgba_to_hex(const GdkRGBA *const rgba);
GdkRGBA *hex_to_gdkrgba(const char *hex_color);

bool set_tag_color(GdkRGBA *color, const char *tag_css_id); 

#endif 
