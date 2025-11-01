#include "tasks.h" 
#include <stdlib.h> 
#include <stdio.h> 
#include "../appconfig/appconfig.h" 
#include "../helpers/date_helpers.h" 
#include "../records/tags.h" 
#include "../helpers/string_helpers.h" 
#include <string.h> 
#include <time.h> 


uint64_t generate_task_id() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

bool update_task(struct Gtask *task) {
    char *home = getenv("HOME");
    char tasks_buff_path[512];
    snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);

    FILE *f = fopen(tasks_buff_path, "r");
    if (!f) {
        perror("fopen failed at update_task (read)");
        return false;
    }

    char tmp_path[sizeof(tasks_buff_path) + 8];
    snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", tasks_buff_path);
    FILE *tmp = fopen(tmp_path, "w");
    if (!tmp) {
        perror("fopen failed at update_task (tmp)");
        fclose(f);
        return false;
    }

    char buffer[2048];
    char *now = date_now();
    uint8_t updated = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        uint64_t current_id = 0;
        sscanf(buffer, "%lu|", &current_id);

        if (current_id == task->id) {
            fprintf(tmp, "%lu|%d|%s|%s|%lu|%s|%s|%d|%s|%s\n",
                task->id, task->done, task->title, task->description,
                task->project_id, now, task->due_date,
                task->priority,
                task->tag != NULL ? task->tag->name : "N/A",
                task->tag != NULL ? task->tag->color : "#FFFFFF");
            updated = 1;
        } else {
            fputs(buffer, tmp);
        }
    }

    fclose(f);
    fclose(tmp);

    if (!updated) {
        fprintf(stderr, "update_task: no task with id %lu found.\n", task->id);
    }

    if (remove(tasks_buff_path) != 0) {
        perror("remove original file failed");
        return false;
    }
    if (rename(tmp_path, tasks_buff_path) != 0) {
        perror("rename tmp file failed");
        return false;
    }

    return true;
}


bool record_new_task(struct Gtask *task){
        
        char *home = getenv("HOME");
        char tasks_buff_path[2 << 8];
        snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);
        
        FILE *f = fopen(tasks_buff_path, "a+");
        if(f == NULL) {
          perror("fopen failed at record_new_task");
          return false;
        }
               
        task->id = generate_task_id();
        char *now = date_now();

        fprintf(f, "%ld|%d|%s|%s|%ld|%s|%s|%d|%s|%s\n",
        task->id, task->done, task->title, task->description,
        task->project_id, now, task->due_date,
        task->priority, task->tag != NULL ? task->tag->name : "N/A",
        task->tag  != NULL ? task->tag->color : "#FFFFFF");


        fclose(f);      
        return true;

}


bool remove_task(uint64_t id) {
    char *home = getenv("HOME");
    char tasks_buff_path[512];
    snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);

    FILE *f = fopen(tasks_buff_path, "r");
    if (!f) {
        perror("fopen failed at remove_task (read)");
        return false;
    }

    char tmp_path[sizeof(tasks_buff_path) + 8];
    snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", tasks_buff_path);
    FILE *tmp = fopen(tmp_path, "w");
    if (!tmp) {
        perror("fopen failed at remove_task (tmp)");
        fclose(f);
        return false;
    }

    char buffer[2048];
    uint8_t removed = 0;

    while (fgets(buffer, sizeof(buffer), f)) {
        uint64_t current_id = 0;
        sscanf(buffer, "%lu|", &current_id);

        if (current_id == id) {
            removed = 1; // Skip this line
            continue;
        }
        fputs(buffer, tmp);
    }

    fclose(f);
    fclose(tmp);

    if (!removed) {
        fprintf(stderr, "remove_task: no task with id %lu found.\n", id);
    }

    remove(tasks_buff_path);
    rename(tmp_path, tasks_buff_path);
    return true;
}

struct Gtask *parse_tasks(const char *input, size_t *out_count) {
    printf("At parse tasks\n");
    char *data = strdup(input); 
    if (data == NULL) return NULL;

    struct Gtask *tasks = NULL;
    size_t count = 0;

    char *line = strtok(data, "\n");
    while (line) {
        tasks = realloc(tasks, sizeof(struct Gtask) * (count + 1));
        struct Gtask *t = &tasks[count];
      
        char *ptr = line;
        char *token;

        token = next_token(&ptr, "|"); t->id = strtoull(token, NULL, 10);
        token = next_token(&ptr, "|"); t->done = (uint8_t)atoi(token);
        token = next_token(&ptr, "|"); strncpy(t->title, token, sizeof(t->title));
        token = next_token(&ptr, "|"); 
        t->description = strdup(token ? token : "");

        token = next_token(&ptr, "|"); t->project_id = strtoull(token, NULL, 10);
        token = next_token(&ptr, "|"); strncpy(t->created_at, token, sizeof(t->created_at));
        token = next_token(&ptr, "|"); strncpy(t->due_date, token, sizeof(t->due_date));
        token = next_token(&ptr, "|"); t->priority = (uint8_t)atoi(token);

        t->tag = malloc(sizeof(struct Gtag));
        memset(t->tag, 0, sizeof(struct Gtag));

        token = next_token(&ptr, "|"); strncpy(t->tag->name, token ? token : "N/A", sizeof(t->tag->name) - 1);
        token = next_token(&ptr, "|"); strncpy(t->tag->color, token ? token : "#FFFFFF", sizeof(t->tag->color) - 1);


        count++;
        line = strtok(NULL, "\n");

    }

    free(data);
    *out_count = count;
    return tasks;
}

struct Gtask *new_default_task(){

  struct Gtask *task = calloc(1, sizeof(struct Gtask));
  if (task == NULL) {
    perror("Error while allocating memory for gtask at new_default_task");
    return NULL;
  }
  
  task->id = 0;
  task->done = 0;
  task->title[0] = '\0';
  task->description = "";
  task->project_id = 0;

  snprintf(task->created_at, sizeof(task->created_at), "%s", date_now());
  snprintf(task->due_date, sizeof(task->due_date), "%s", date_now());
  task->priority = TASK_PRIORITY_UNKNOW;



  task->tag = calloc(1, sizeof(struct Gtag));
    if (!task->tag) {
        perror("Error allocating Gtag");
        free(task);
        return NULL;
  }

  task->tag->name[0] = '\0';
  task->tag->color[0] = '\0';



  return task;

}

