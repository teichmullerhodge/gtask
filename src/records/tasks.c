#include "tasks.h" 
#include <stdlib.h> 
#include <stdio.h> 
#include "../appconfig/appconfig.h" 
#include "../helpers/date_helpers.h" 
#include "../records/tags.h" 


uint8_t record_new_task(char *title, 
        char *desc, 
        uint64_t *proj_id,
        char *due_date,
        enum TaskPriority priority,
        struct Gtag *tag){
        
        char *home = getenv("HOME");
        char tasks_buff_path[2 << 8];
        snprintf(tasks_buff_path, sizeof(tasks_buff_path), "%s/%s", home, GTASKS_RECORD_PATH);
        
        FILE *f = fopen(tasks_buff_path, "a+");
        if(f == NULL) {
          perror("fopen failed at record_new_task");
          return 1;
        }
        
        uint64_t lines = 0;
        char character;
        uint8_t last_char_was_newline = 1;
        while((character = fgetc(f)) != EOF) {
          if(character == '\n') {
            lines++;
            last_char_was_newline = 1;
          } else {
            last_char_was_newline = 0;
          } 
        }

        if(!last_char_was_newline) lines++;
        uint64_t id = lines; 
        struct Gtask task = {0};
        task.id = id;
        task.done = 0;

        snprintf(task.title, sizeof(task.title), "%s", title);



        task.description = desc; 
        task.project_id = proj_id != NULL ? *proj_id : 0; 
        char *now = date_now();
        
        snprintf(task.created_at, sizeof(task.created_at), "%s", now);
        snprintf(task.due_date, sizeof(task.due_date), "%s", due_date);
        task.priority = priority;
        


        if(tag != NULL) {
          task.tag = tag; 
          snprintf(tag->name, sizeof(tag->name), "%s", task.tag->name);
          snprintf(tag->color, sizeof(tag->color), "%s", task.tag->color); 
        }
        
        if(task.tag == NULL){
          task.tag = default_tag(); 
        }

        fprintf(f, "%ld|%d|%s|%s|%ld|%s|%s|%d|%s|%s\n",
        task.id, task.done, task.title, task.description,
        task.project_id, task.created_at, task.due_date,
        task.priority, task.tag ? task.tag->name : "",
        task.tag ? task.tag->color : "");


        fclose(f);

    
        
        return 0;

}
