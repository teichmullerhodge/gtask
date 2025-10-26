#include "string_helpers.h" 


#include <string.h> 


char* next_token(char **str, const char *delim){
  
    char *start = *str;
    if (start == NULL) return NULL;

    char *p = strpbrk(start, delim);
    if(p != NULL){
        *p = '\0';
        *str = p + 1;
    } else {
      *str = NULL;
    }
  
    return start;
}

