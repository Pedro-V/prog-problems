#include <stdio.h>
#include <stdlib.h>

#define EPS 0.001
#define f_eq(f1, f2) (abs(f1 - f2) < EPS)
#define MAX

typedef struct edge {
  int to;
  double flow;
  struct edge *next;
} edge;

int enough_liquid(double liters, edge *root) {
  if (root->children == NULL) {
    return root->needed_liquid == liters;
  }
}
