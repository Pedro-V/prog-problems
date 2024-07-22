#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 0.0001
#define MAX_NODES 1000
#define MAX_LITERS 2000000000
//#define MAX_LITERS 20
#define square(x) (x * x)

typedef struct edge {
  int to;
  double flow;
  int is_super_pipe;
  struct edge *next;
} edge;

int can_feed(edge *adj_list[], int node, double liters, int ants[]) {
  if (ants[node] != -1)
    return liters >= ants[node];

  double down_pipe;
  int all_enough = 1;
  edge *e = adj_list[node];
  while (e && all_enough) {
    down_pipe = liters * e->flow;
    if (e->is_super_pipe)
      down_pipe = square(down_pipe);
    all_enough = can_feed(adj_list, e->to, down_pipe, ants);
    e = e->next;
  }

  return all_enough;
}

void solve(edge *adj_list[], int ants[]) {
  double low, high, mid;
  low = 0, high = MAX_LITERS;
  while (high - low > EPS) {
    mid = (low + high) / 2;
    if (can_feed(adj_list, 1, mid, ants))
      high = mid;
    else
      low = mid;
  }

  printf("%.3lf\n", high);
}

int main() {
  edge *adj_list[MAX_NODES + 1] = {NULL}, *e;
  int i, num_nodes, from, to, flow, is_super_pipe;
  int ants[MAX_NODES + 1];

  scanf("%d", &num_nodes);
  for (i = 0; i < num_nodes - 1; i++) {
    scanf("%d %d %d %d", &from, &to, &flow, &is_super_pipe);

    e = malloc(sizeof(edge));
    e->to = to;
    e->flow = flow / 100.0;
    e->is_super_pipe = is_super_pipe;
    e->next = adj_list[from];
    adj_list[from] = e;
  }

  for (i = 1; i <= num_nodes; i++)
    scanf("%d", &ants[i]);

  solve(adj_list, ants);
}
