#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 50
#define OP_LEN 6

FILE *input, *output;

typedef struct node {
  char name[NAME_LEN + 1];
  struct node *prev, *next;
} node;

node *search(node *begin, char *name) {
  node *person = begin;

  if (!begin)
    return NULL;

  while (person->next != begin && strcmp(person->name, name) != 0)
    person = person->next;

  if (strcmp(person->name, name) == 0)
    return person;
  else
    return NULL;
}

void show(node *begin, char *name) {
  node *person = search(begin, name);
  if (person)
    fprintf(output, "[ OK  ] %s<-%s->%s\n", person->prev->name, name, person->next->name);
  else
    fprintf(output, "[ERROR] ?<-%s->?\n", name);
}

node *add_person(node *begin, char *name) {
  node *new_person = malloc(sizeof(node));
  strcpy(new_person->name, name);

  if (!begin) {
    new_person->next = new_person;
    new_person->prev = new_person;
  }
  else if (search(begin, name)) {
    fprintf(output, "[ERROR] ADD %s\n", name);
    return begin;
  }
  else {
    new_person->prev = begin->prev;
    begin->prev->next = new_person;
    begin->prev = new_person;
    new_person->next = begin;
  }

  fprintf(output, "[ OK  ] ADD %s\n", name);
  return new_person;
}

node *remove_person(node *begin, char *name) {
  node *person = search(begin, name);

  if (!person) {
    fprintf(output, "[ERROR] REMOVE %s\n", name);
    return begin;
  }

  person->prev->next = person->next;
  person->next->prev = person->prev;

  fprintf(output, "[ OK  ] REMOVE %s\n", name);

  if (person == begin) {
    if (begin->next == begin)
      return NULL;
    else
      return begin->next;
  }
  else return begin;
}

int main(int argc, char **argv) {
  char op[OP_LEN + 1], name[NAME_LEN + 1];
  input = fopen(argv[1], "r");
  output = fopen(argv[2], "w");
  if (!input || !output) {
    printf("Error opening input/output files.\n");
    exit(EXIT_FAILURE);
  }
  node *begin = NULL;

  while (fscanf(input, "%s %[^\n]", op, name) != EOF) {
    if (strcmp(op, "ADD") == 0)
      begin = add_person(begin, name);
    else if (strcmp(op, "REMOVE") == 0)
      begin = remove_person(begin, name);
    else
      show(begin, name);
  }

  fclose(input);
  fclose(output);
}
