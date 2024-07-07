#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 10
#define MAX_NODES 1000

typedef struct node {
  int num_children;
  struct node **children;
  char name[MAX_CHARS + 1];
  int score;
} node;

// Handle tree construction by keeping an array of nodes and linear search it to
// check for node occurrence. Since MAX_NODES == 1000, this isn't very expensive.
node *find_node(node *nodes[], int num_nodes, char *name) {
  for (int i = 0; i < num_nodes; i++)
    if (strcmp(nodes[i]->name, name) == 0)
      return nodes[i];
  return NULL;
}

node *new_node(char *name) {
  node *n = malloc(sizeof(node));
  strcpy(n->name, name);
  n->num_children = 0;
  n->score = 0;
  return n;
}

int read_tree(node *nodes[], int num_lines) {
  node *parent_node, *child_node;
  char parent_name[MAX_CHARS + 1], child_name[MAX_CHARS + 1];
  int i, j, num_children;
  int num_nodes = 0;
  for (i = 0; i < num_lines; i++) {
    scanf("%s %d", parent_name, &num_children);
    parent_node = find_node(nodes, num_nodes, parent_name);

    if (parent_node == NULL) {
      parent_node = new_node(parent_name);
      nodes[num_nodes] = parent_node;
      num_nodes++;
    }
    parent_node->children = malloc(sizeof(node) * num_children);
    parent_node->num_children = num_children;

    for (j = 0; j < num_children; j++) {
      scanf("%s", child_name);
      child_node = find_node(nodes, num_nodes, child_name);
      if (child_node == NULL) {
        child_node = new_node(child_name);
        nodes[num_nodes] = child_node;
        num_nodes++;
      }
      parent_node->children[j] = child_node;
    }
  }

  return num_nodes;
}

// Just use recursion for calculating the score.
int score_one(node *n, int d) {
  if (d == 1)
    return n->num_children;
  int score = 0;
  for (int i = 0; i < n->num_children; i++) {
    score += score_one(n->children[i], d-1);
  }
  return score;
}

void score_all(node *nodes[], int num_nodes, int d) {
  for (int i = 0; i < num_nodes; i++)
    nodes[i]->score = score_one(nodes[i], d);
}

int cmp_score(const void *a, const void *b) {
  const node *n1 = *(const node **)a;
  const node *n2 = *(const node **)b;

  if (n1->score > n2->score)
    return -1;
  if (n2->score > n1->score)
    return 1;
  
  return strcmp(n1->name, n2->name);
}

void output_info(node *nodes[], int num_nodes, int case_num) {
  printf("Tree %d:\n", case_num);
  int i = 0;
  while (nodes[i]->score > 0 && i < 3) {
    printf("%s %d\n", nodes[i]->name, nodes[i]->score);
    i++;
    while (i < num_nodes && nodes[i]->score == nodes[i-1]->score) {
      printf("%s %d\n", nodes[i]->name, nodes[i]->score);
      i++;
    }
  }
}

int main() {
  static node *nodes[MAX_NODES];
  int num_cases, n, d, num_nodes;
  scanf("%d", &num_cases);
  for (int case_num = 1; case_num <= num_cases; case_num++) {
    scanf("%d %d", &n, &d);
    num_nodes = read_tree(nodes, n);
    score_all(nodes, num_nodes, d);
    qsort(nodes, num_nodes, sizeof(node*), cmp_score);
    output_info(nodes, num_nodes, case_num);
    if (case_num < num_cases)
      printf("\n");
  }
}
