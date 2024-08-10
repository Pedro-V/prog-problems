#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 50
#define min(a, b) (a < b ? a : b)

FILE *input, *output;

typedef struct {
  char name[NAME_LEN + 1];
  int pages;
} doc;

typedef struct node {
  doc document;
  struct node *next;
} node;

typedef struct {
  char name[NAME_LEN + 1];
  int current_load;
  node *stack;
} printer;

void print_stack(node *stack, int per_line) {
  node *n = stack;
  while (n) {
    if (!per_line)
      putc(' ', output);

    fprintf(output, "%s-%dp", n->document.name, n->document.pages);

    if (per_line || n->next == NULL)
      putc('\n', output);
    else
      putc(',', output);

    n = n->next;
  }
}
void show_printer_history(printer p) {
  fprintf(output, "[%s]", p.name);
  print_stack(p.stack, 0);
}

node *push(node *stack, doc document) {
  node *new_node = malloc(sizeof(node));
  new_node->document = document;
  new_node->next = stack;
  return new_node;
}

void solve(int num_printers, int num_docs, printer *printers, node *main_stack, doc *docs) {
  int i, new_load, more = 1, next_doc_index = 0;
  int curr_min_pages = 0, next_min_pages = -1, total_pages = 0;

  while (more) {
    more = 0;
    for (i = 0; i < num_printers; i++) {
      new_load = printers[i].current_load - curr_min_pages;
      printers[i].current_load = new_load < 0 ? -1 : new_load;

      if (printers[i].current_load == 0 && printers[i].stack != NULL) {
        main_stack = push(main_stack, printers[i].stack->document);
        total_pages += printers[i].stack->document.pages;
      }

      if (printers[i].current_load == 0 && next_doc_index < num_docs) {
        if (next_min_pages == -1 || docs[next_doc_index].pages < next_min_pages)
          next_min_pages = docs[next_doc_index].pages;

        printers[i].current_load = docs[next_doc_index].pages;
        printers[i].stack = push(printers[i].stack, docs[next_doc_index]);
        show_printer_history(printers[i]);
        next_doc_index += 1;
        more = 1;
      }
      else if (printers[i].current_load > 0) {
        if (next_min_pages == -1 || printers[i].current_load < next_min_pages)
          next_min_pages = printers[i].current_load;
        more = 1;
      }
    }
    curr_min_pages = next_min_pages;
    next_min_pages = -1;
  }

  fprintf(output, "%dp\n", total_pages);
  print_stack(main_stack, 1);
}

int main(int argc, char **argv) {
  int i, num_printers, num_docs;
  printer *printers;
  doc *docs;
  node *main_stack = NULL;

  input = fopen(argv[1], "r");
  output = fopen(argv[2], "w");
  if (!input || !output) {
    printf("Error opening files.\n");
    exit(EXIT_FAILURE);
  }

  fscanf(input, "%d", &num_printers);
  printers = malloc(sizeof(printer) * num_printers);
  for (i = 0; i < num_printers; i++) {
    fscanf(input, "%s", printers[i].name);
    printers[i].stack = NULL;
    printers[i].current_load = 0;
  }

  fscanf(input, "%d", &num_docs);
  docs = malloc(sizeof(doc) * num_docs);
  for (i = 0; i < num_docs; i++)
    fscanf(input, "%s %d", docs[i].name, &docs[i].pages);

  solve(num_printers, num_docs, printers, main_stack, docs);
}
