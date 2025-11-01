#ifndef TASKS_H
#define TASKS_H 

#include <stdlib.h> 
#include <stdbool.h> 
#include <stdint.h>
#include "tags.h" 
#include <stdbool.h>


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
  char created_at[36]; // Format: YYYY-MM-DD HH:MM 
  char due_date[36];
  enum TaskPriority priority;
  struct Gtag* tag; 
};



uint64_t generate_task_id();
struct Gtask *parse_tasks(const char *input, size_t *out_count);     



bool record_new_task(struct Gtask *task);
bool remove_task(uint64_t id);
bool update_task(struct Gtask *task);       

struct Gtask *new_default_task();

#endif 
