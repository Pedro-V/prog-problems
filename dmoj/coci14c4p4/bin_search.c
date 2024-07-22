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

int feed_ants(edge *tree[], int node, double liters, int ants[]) {
  if (ants[node] != -1)
    return liters >= ants[node];

  int enough, all_enough = 1;
  edge *e = tree[node];
  while (e) {
    enough = feed_ants(tree, e->to, liters * e->flow, ants);
    if (!enough && e->is_super_pipe)
      enough = feed_ants(tree, e->to, square(liters * e->flow), ants);

    all_enough = all_enough && enough;
    e = e->next;
  }

  return all_enough;
}

double find_liters(edge *tree[], int ants[]) {
  int cur_valid = 0, prev_valid = 0;
  double cur_liters = 0, prev_liters = 0;
  double a = 0, b = MAX_LITERS;
  do {
    prev_liters = cur_liters;
    prev_valid = cur_valid;
    cur_liters = (a + b) / 2;
    cur_valid = feed_ants(tree, 1, cur_liters, ants);

    if (cur_valid)
      b = cur_liters;
    else
      a = cur_liters;
  } while ((!prev_valid || !cur_valid) || fabs(cur_liters - prev_liters) > EPS);

  return cur_liters;
}

void solve(edge *tree[], int ants[]) {
  double liters = find_liters(tree, ants);
  printf("%.3lf\n", liters);
}

int main() {
  edge *tree[MAX_NODES + 1] = {NULL}, *e;
  int i, num_nodes, from, to, flow, is_super_pipe;
  int ants[MAX_NODES + 1];

  scanf("%d", &num_nodes);
  for (i = 0; i < num_nodes - 1; i++) {
    scanf("%d %d %d %d", &from, &to, &flow, &is_super_pipe);

    e = malloc(sizeof(edge));
    e->to = to;
    e->flow = flow / 100.0;
    e->is_super_pipe = is_super_pipe;
    e->next = tree[from];
    tree[from] = e;
  }

  for (i = 1; i <= num_nodes; i++)
    scanf("%d", &ants[i]);

  solve(tree, ants);
}
