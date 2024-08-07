#include <stdio.h>

#define MAX_DRAWERS 300000

int find(int parent[], int drawer) {
  int temp, current = drawer;

  while (parent[current] != current)
    current = parent[current];

  while (parent[drawer] != current) {
    temp = parent[drawer];
    parent[drawer] = current;
    current = temp;
  }

  return current;
}

// Unions drawer1's set to drawer2's set, always.
int union_sets(int parent[], int drawer1, int drawer2) {
  int set1, set2;

  set1 = find(parent, drawer1);
  set2 = find(parent, drawer2);

  parent[set2] = set1;
  return set1;
}

int would_cycle(int parent[], int occupied[], int drawer) {
  int set = find(parent, drawer);
  return occupied[set];
}

int same_set(int drawer1, int drawer2, int parent[]) {
  return find(parent, drawer1) == find(parent, drawer2);
}

int ladica(int parent[], int occupied[], int drawer1, int drawer2) {
  if (!occupied[drawer1]) {
    occupied[drawer1] = 1;
    // We only perform Union if the drawers aren't in the same set.
    // Doing so would create an actual cycle in the structure.
    // We only "signal" these cycles by having the representative being occupied.
    if (!same_set(drawer1, drawer2, parent))
      union_sets(parent, drawer1, drawer2);
    return 1;
  }

  if (!occupied[drawer2]) {
    occupied[drawer2] = 1;
    if (!same_set(drawer1, drawer2, parent))
      union_sets(parent, drawer2, drawer1);
    return 1;
  }

  if (occupied[drawer1] && !would_cycle(parent, occupied, drawer1)) {
    union_sets(parent, drawer1, drawer2);
    return 1;
  }

  if (occupied[drawer2] && !would_cycle(parent, occupied, drawer2)) {
    union_sets(parent, drawer2, drawer1);
    return 1;
  }

  return 0;
}

int main() {
  static int parent[MAX_DRAWERS + 1], occupied[MAX_DRAWERS + 1];
  int i, num_items, num_drawers;
  int drawer1, drawer2;

  scanf("%d %d", &num_items, &num_drawers);

  for (i = 1; i <= num_drawers; i++) {
    parent[i] = i;
    occupied[i] = 0;
  }

  for (i = 0; i < num_items; i++) {
    scanf("%d %d", &drawer1, &drawer2);
    if (ladica(parent, occupied, drawer1, drawer2))
      printf("LADICA\n");
    else
      printf("SMECE\n");
  }
}
