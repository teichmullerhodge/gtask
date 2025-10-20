#include "tags.h" 


#include <stdlib.h>
#include <stdio.h> 
#include <string.h>


struct Gtag* default_tag() {
    struct Gtag* tag = malloc(sizeof(struct Gtag));
    if(tag == NULL) {
        perror("Malloc failed at default_tag");
        return NULL;
    }

   memset(tag, 0, sizeof(struct Gtag));

   strncpy(tag->name, "N/A", sizeof(tag->name) - 1);
   strncpy(tag->color, "#FFFFFF", sizeof(tag->color) - 1);

    return tag;
}

