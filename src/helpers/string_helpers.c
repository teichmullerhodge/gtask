#include "string_helpers.h" 


#include <string.h> 

#include <stdbool.h>

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

void sanitize_string(char *mut_str){
  
  size_t len = strlen(mut_str);
  for(size_t k = 0; k < len; k++){
    bool should_sanitize = !(mut_str[k] >= 'a' && mut_str[k] <= 'z') && 
                           !(mut_str[k] >= 'A' && mut_str[k] <= 'Z') && 
                           !(mut_str[k] >= '0' && mut_str[k] <= '9');
    
    mut_str[k] = should_sanitize ? '_' : mut_str[k];

  }
}

