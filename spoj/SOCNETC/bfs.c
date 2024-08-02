#include <stdio.h>
#include <stdlib.h>

// BFS is suboptimal. In the worst case, where all Q operations are adds, we
// perform two BFS calls, both costing q (the then current size of the graph), on each add operation.
// In total, we have Q + (Q - 1) + (Q - 2) + .. + 1 = O(Q^2) time complexity.

// This is due to the fact that BFS solves a more general problem:
// Single-Source Shortest Paths in unweighted graphs, where here we don't need
// to solve that, only add edges, check for reachability and size of subgraphs.

#define MAX_NODES 100000

typedef struct node {
  int idx;
  struct node *next;
} node;

typedef struct pair {
  int size, are_friends;
} pair;

// This answers both questions: size of the community and whether x and y are friends.
// If one wishes only size, pass -1 for the last parameter.
pair bfs(node *adj_list[], int num_nodes, int x, int y) {
  static int board[MAX_NODES + 1];
  static int cur_nodes[MAX_NODES], num_cur_nodes = 0;
  static int next_nodes[MAX_NODES], num_next_nodes = 0;
  int i;
  pair result = { 1, 0 };
  node *n;

  for (i = 1; i <= num_nodes; i++)
    board[i] = -1;

  cur_nodes[0] = x;
  num_cur_nodes = 1;
  board[x] = 1;

  while (num_cur_nodes > 0) {
    num_next_nodes = 0;

    for (i = 0; i < num_cur_nodes; i++) {
      n = adj_list[cur_nodes[i]];
      while (n) {
        if (board[n->idx] == -1) {
          board[n->idx] = 1;
          next_nodes[num_next_nodes++] = n->idx;
          result.size++;
          if (y != -1 && n->idx == y)
            result.are_friends = 1;
        }
        n = n->next;
      }
    }

    for (i = 0; i < num_next_nodes; i++)
      cur_nodes[i] = next_nodes[i];
    num_cur_nodes = num_next_nodes;
  }

  if (x == y)
    result.are_friends = 1;

  return result;
}

int size(node *adj_list[], int num_nodes, int x) {
  return bfs(adj_list, num_nodes, x, -1).size;
}

int examine(node *adj_list[], int num_nodes, int x, int y) {
  return bfs(adj_list, num_nodes, x, y).are_friends;
}

void add(node *adj_list[], int num_nodes, int max_size, int x, int y) {
  int size_x, size_y;
  node *n1, *n2;

  size_x = size(adj_list, num_nodes, x);
  size_y = size(adj_list, num_nodes, y);

  if (size_x + size_y > max_size)
    return;

  n1 = malloc(sizeof(node));
  n2 = malloc(sizeof(node));

  n1->idx = y;
  n1->next = adj_list[x];
  adj_list[x] = n1;

  n2->idx = x;
  n2->next = adj_list[y];
  adj_list[y] = n2;
}

int main() {
  static node *adj_list[MAX_NODES + 1] = {NULL};
  int num_nodes, max_size, num_ops;
  int i, x, y;
  char op;

  scanf("%d %d ", &num_nodes, &max_size);
  scanf("%d ", &num_ops);
  for (i = 0; i < num_ops; i++) {
    op = getchar();

    if (op == 'S') {
      scanf("%d ", &x);
      printf("%d\n", size(adj_list, num_nodes, x));
    } else {
      scanf("%d %d ", &x, &y);
      if (op == 'A')
        add(adj_list, num_nodes, max_size, x, y);
      else
        printf("%s\n", examine(adj_list, num_nodes, x, y) ? "Yes" : "No");
    }
  }
}
