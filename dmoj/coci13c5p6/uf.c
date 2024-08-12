#include <stdio.h>

// This is a Union-Find solution.
// To see why UF is useful, first model the problem/samples as a graph,
// and note that a search for the drawer that is empty is constantly performed.
//
// Ignore for a moment the possibility of cyclic chains of drawers, and 
// let the empty drawer in the end of a chain/set of drawers be the representative
// of that chain/set.
//
// Then, checking if we can apply rules 3/4 is a FIND.
//
// Consider also the situation where a new item has drawers X and Y, and suppose
// we can put the item on X by following the problem's spec.
// This means the item we just put on X will be capable of being moved to Y in
// the future if the representative of Y's set is empty.
// This is an UNION of X's set to Y's set. Note that the order we perform unions
// is not arbitrary, and this disables union-by-size optimization.
//
// I didn't find any way of handling cyclic chains just by using the UF
// structure. I brought in an 'occupied' array, and don't actually perform
// unions that would led to cycles, I just set this array.

#define MAX_DRAWERS 300000

int find(int parent[], int drawer) {
  int temp, current = drawer;

  while (parent[current] != current)
    current = parent[current];

  while (parent[drawer] != current) {
    temp = parent[drawer];
    parent[drawer] = current;
    drawer = temp;
  }

  return current;
}

// Unions drawer1's set to drawer2's set, always.
int union_sets(int parent[], int occupied[], int drawer1, int drawer2) {
  int set1, set2;

  set1 = find(parent, drawer1);
  set2 = find(parent, drawer2);

  // If we are performing Union, it means set1 will be occupied.
  occupied[set1] = 1;
  parent[set1] = set2;

  return set2;
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
      union_sets(parent, occupied, drawer1, drawer2);
    return 1;
  }

  if (!occupied[drawer2]) {
    occupied[drawer2] = 1;
    if (!same_set(drawer1, drawer2, parent))
      union_sets(parent, occupied, drawer2, drawer1);
    return 1;
  }

  if (occupied[drawer1] && !would_cycle(parent, occupied, drawer1)) {
    union_sets(parent, occupied, drawer1, drawer2);
    return 1;
  }

  if (occupied[drawer2] && !would_cycle(parent, occupied, drawer2)) {
    union_sets(parent, occupied, drawer2, drawer1);
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
