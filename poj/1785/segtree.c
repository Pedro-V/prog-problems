/*
 * Similar to recursion.c, but uses segment trees to efficiently answer
 * Range Maximum Queries (RMQs) in O(log n).
 *
 * This formulation is due to Daniel Zingaro, 2024.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 50000
#define LABEL_LENGTH 16

/*
 * Treap definitions.
 */
#define MAX_NODES 50000

typedef struct {
  char *label;
  int priority;
} treap_node;

/*
 * Utils.
 */
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

//int max_priority_index(treap_node treap_nodes[], int left, int right) {}

/*
 * Segment Tree definitions.
 *
 * A segment tree is a complete binary tree, therefore we can store it in an
 * array (with some waste).
 */

typedef struct {
  int left, right;
  int max_index;
} segtree_node;

void init_segtree(segtree_node segtree[], int node, int left, int right) {
  int mid;

  segtree[node].left = left;
  segtree[node].right = right;

  if (left == right)
    return;

  mid = (left + right) / 2;
  init_segtree(segtree, node * 2, left, mid);
  init_segtree(segtree, node * 2 + 1, mid + 1, right);
}

// Fills the segment tree with the answer to the RMQ:
// What is the index of the maximum element in the segment? Also, return this index.
int fill_segtree(segtree_node segtree[], int node, treap_node treap_nodes[]) {
  if (segtree[node].left == segtree[node].right) {
    segtree[node].max_index = segtree[node].left;
    return segtree[node].max_index;
  }

  int left_max, right_max;
  left_max = fill_segtree(segtree, 2*node, treap_nodes);
  right_max = fill_segtree(segtree, 2*node + 1, treap_nodes);

  if (treap_nodes[left_max].priority > treap_nodes[right_max].priority)
    segtree[node].max_index = left_max;
  else
    segtree[node].max_index = right_max;

  return segtree[node].max_index;
}

// Performs a RMQ in the segment tree.
int query_segtree(segtree_node segtree[], treap_node treap_nodes[], int node, int left, int right) {
  int left_max, right_max;

  // Case 1: This segment has no index in common with the query's range.
  if (left > segtree[node].right || right < segtree[node].left)
    return -1;

  // Case 2: This segment is completely contained in the query's range.
  if (left <= segtree[node].left && segtree[node].right <= right)
    return segtree[node].max_index;

  // Case 3: Otherwise (The segment is partially contained in the query's range),
  // search on both subtrees and act accordingly.
  left_max = query_segtree(segtree, treap_nodes, 2 * node, left, right);
  right_max = query_segtree(segtree, treap_nodes, 2 * node + 1, left, right);

  if (left == -1)
    return right_max;
  if (right == -1)
    return left_max;

  if (treap_nodes[left_max].priority > treap_nodes[right_max].priority)
    return left_max;
  return right_max;
}

void solve(treap_node treap_nodes[], segtree_node segtree[], int left, int right) {
  int max_index;

  if (left > right)
    return;

  max_index = query_segtree(segtree, treap_nodes, 1, left, right);

  printf("(");
  solve(treap_nodes, segtree, left, max_index - 1);
  printf("%s/%d", treap_nodes[max_index].label, treap_nodes[max_index].priority);
  solve(treap_nodes, segtree, max_index + 1, right);
  printf(")");
}

int main() {
  static treap_node treap_nodes[MAX_NODES];
  // For a segment tree representing an array of n nodes, we can safely represent it as an
  // array of size 4*n (Proof in Zingaro, 2024).
  // Add + 1 so that we start indexing at 1.
  static segtree_node segtree[MAX_NODES * 4 + 1];
  int i, num_nodes;

  scanf("%d ", &num_nodes);
  while (num_nodes > 0) {
    for (i = 0; i < num_nodes; i++) {
      treap_nodes[i].label = read_label(LABEL_LENGTH);
      scanf("%d ", &treap_nodes[i].priority);
    }
    qsort(treap_nodes, num_nodes, sizeof(treap_node), compare);
    init_segtree(segtree, 1, 0, num_nodes - 1);
    fill_segtree(segtree, 1, treap_nodes);
    solve(treap_nodes, segtree, 0, num_nodes - 1);
    printf("\n");
    scanf("%d ", &num_nodes);
  }

  return 0;
}
