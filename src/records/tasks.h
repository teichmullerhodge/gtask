#ifndef TASKS_H
#define TASKS_H 


#include <stdbool.h> 
#include <stdint.h>
#include "tags.h" 

enum TaskPriority {
  TASK_PRIORITY_UNKNOW,
  TASK_PRIORITY_LOW,
  TASK_PRIORITY_MEDIUM,
  TASK_PRIORITY_HIGH,
  TASK_PRIORITY_CRITICAL
};

struct Gtask {
  uint64_t id;
  uint8_t done;
  char title[2 << 6];
  char *description;
  uint64_t project_id;
  char created_at[20]; // Format: YYYY-MM-DD HH:MM 
  char due_date[20];
  enum TaskPriority priority;
  struct Gtag* tag; 
};

                    

uint8_t record_new_task(char *title, 
        char *desc, 
        uint64_t *proj_id,
        char *due_date,
        enum TaskPriority priority,
        struct Gtag *tag);
       

#endif 
