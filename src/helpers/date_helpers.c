#include "date_helpers.h" 

#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 

char *date_now(void){
    time_t rawtime;
    struct tm info;
    char *buff = malloc(80);
    if(buff == NULL) {
        perror("Malloc failed at date_now");
        return NULL;
    }

    time(&rawtime);
    if (localtime_r(&rawtime, &info) == NULL) {
        free(buff);
        return NULL;
    }

    if (strftime(buff, 80, "%Y-%m-%d %H:%M", &info) == 0) {
        buff[0] = '\0';
    }
    return buff;
}

