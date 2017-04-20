#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1000

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_a_lst();
void split_line();

//node class
struct clip {
  int views;
  char *user;
  char *id;
  char *title;
  char *time;
  struct clip *next;
} 

*head;

//returns length
int find_length(struct clip *head){
  struct clip *current = head;
  int count = 0;

  while(current != NULL){
    count++;
    current = current->next;
  }

  return count;

}

//builds list, finds length, prints amount of 'clips', prints the linked list
int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  n = find_length(head);
  printf("%d clips\n",n);
  print_a_lst(head);
  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp, *cp;
  char *fields[5];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

  if((fp = fopen(fn, "r")) != NULL){

    while(fgets(line, LINE_LENGTH, fp) != NULL){
      split_line(&fields, line);
      hp = append(hp, fields);
    }

    fclose(fp);
  }

  return hp;
}

/* fields will have four values stored upon return */
void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",";

  token = strtok(line, delim);

  while(token != NULL){

    fields[i] = malloc(strlen(token));
    strcpy(fields[i], token);
    token = strtok(NULL, delim);
    i++;

  }
}

/* set four values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;

  tp = malloc(sizeof(struct clip));
  tp -> views = atoi(*five);

  tp -> id = malloc(strlen(five[1]));
  strcpy(tp -> id, five[1]);

  tp -> user = malloc(strlen(five[2]));
  strcpy(tp -> user, five[2]);

  tp -> title = malloc(strlen(five[3]));
  strcpy(tp -> title, five[3]);

  tp -> time = malloc(strlen(five[4]));
  strcpy(tp -> time, five[4]);

  cp = hp;
  if(hp == NULL){
    hp = tp;
  } else{
    while(cp -> next != NULL){
      cp = cp -> next;
    }
    cp -> next = tp;
  }

  return hp;
}

void print_a_lst(struct clip *cp) {

  while(cp -> next != NULL){
    printf("%d,%s,%s,%s,%s\n", cp->views, cp->id, cp->user, cp->title, cp->time);
    cp = cp->next;
  }

  printf("%d,%s,%s,%s,%s\n", cp->views, cp->id, cp->user, cp->title, cp->time);

}
