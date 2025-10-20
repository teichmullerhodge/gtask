#ifndef TAGS_H 
#define TAGS_H 


struct Gtag {
  
  char name[2 << 5];
  char color[(2 << 2) + 1]; //#RRGGBB 

};

struct Gtag* default_tag();


#endif 
