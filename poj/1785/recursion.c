#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 50000
#define LABEL_LENGTH 16

typedef struct {
  char *label;
  int priority;
} treap_node;

char *read_label(int len) {
  int size = 0;
  char c, *label = malloc(len);

  while ((c = getchar()) != '/') {
    label[size++] = c;
    if (size == len) {
      len *= 2;
      label = realloc(label, len);
    }
  }
  label[size] = '\0';
  return label;
}

int compare(const void *v1, const void *v2) {
  const treap_node *n1 = v1, *n2 = v2;
  return strcmp(n1->label, n2->label);
}

// This is a linear search to solve range maximum queries (RMQs).
// In inputs where the maximum element is always
int max_priority_index(treap_node treap_nodes[], int left, int right) {
  int i, max_index = left;
  for (i = left + 1; i <= right; i++)
    if (treap_nodes[i].priority > treap_nodes[max_index].priority)
      max_index = i;
  return max_index;
}

void solve(treap_node treap_nodes[], int left, int right) {
  int root_index;
  treap_node root;

  if (left > right)
    return;

  root_index = max_priority_index(treap_nodes, left, right);
  root = treap_nodes[root_index];

  printf("(");
  solve(treap_nodes, left, root_index - 1);
  printf("%s/%d", root.label, root.priority);
  solve(treap_nodes, root_index + 1, right);
  printf(")");
}

int main() {
  static treap_node treap_nodes[MAX_NODES];
  int num_nodes, i;

  scanf("%d ", &num_nodes);
  while (num_nodes > 0) {
    for (i = 0; i < num_nodes; i++) {
      treap_nodes[i].label = read_label(LABEL_LENGTH);
      scanf("%d ", &treap_nodes[i].priority);
      printf("text: '%s', priority: %d\n", treap_nodes[i].label, treap_nodes[i].priority);
    }
    qsort(treap_nodes, num_nodes, sizeof(treap_node), compare);
    solve(treap_nodes, 0, num_nodes - 1);
    printf("\n");
    scanf("%d ", &num_nodes);
  }

  return 0;
}
