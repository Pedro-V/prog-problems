#include <stdio.h>
#include <stdlib.h>

#define SIZE 700
#define MOD 1000000

/*
 * This adapts Dijkstra's algorithm with a state for holding the box.
 * This formulation is due to section 6.2 of Daniel Zingaro's Algorithmic Thinking.
 */

typedef struct edge {
  int to, length;
  struct edge *next;
} edge;

void solve(edge *adj_list[], int num_towns, int store[]) {
  static int done[2][SIZE + 1], 
             min_distances[2][SIZE + 1],
             num_paths[2][SIZE + 1]; // To find how many paths.
  int i, j, state, found;
  int min_distance, min_town_index, min_state_index, old_distance;
  edge *e;

  for (state = 0; state <= 1; state++)
    for (i = 1; i <= num_towns; i++) {
      done[state][i] = 0;
      min_distances[state][i] = -1;
    }
  min_distances[0][1] = 0;
  num_paths[0][1] = 1;

  for (i = 0; i < num_towns * 2; i++) {
    // Find the next vertex.
    min_distance = -1;
    found = 0;
    for (state = 0; state <= 1; state++)
      for (j = 1; j <= num_towns; j++) {
        // Effectively, we break ties in the search for the miminum distance by
        // giving preference to state 0 nodes.
        // This is a necessary condition for the algorithm's correctness
        // Simulate both tie-breaking strategies on sample3.input to see why.
        if (
          !done[state][j] && min_distances[state][j] >= 0 &&
          (min_distance == -1 || min_distances[state][j] < min_distance)
        ) {
          min_distance = min_distances[state][j];
          min_town_index = j;
          min_state_index = state;
          found = 1;
        }
      }
    if (!found)
      break;
    done[min_state_index][min_town_index] = 1;

    // First handle the possible transition from state-0 subgraph to state-1 subgraph.
    if (min_state_index == 0 && store[min_town_index]) {
      old_distance = min_distances[1][min_town_index];

      if (old_distance == -1 || old_distance > min_distance) {
        min_distances[1][min_town_index] = min_distance;
        num_paths[1][min_town_index] = num_paths[0][min_town_index];
      } else if (old_distance == min_distance)
        num_paths[1][min_town_index] += num_paths[0][min_town_index];

      num_paths[1][min_town_index] %= MOD;

    // Then just go back to old Dijkstra.
    } else {
      e = adj_list[min_town_index];
      while (e) {
        old_distance = min_distances[min_state_index][e->to];

        if (old_distance == -1 || old_distance > min_distance + e->length) {
          min_distances[min_state_index][e->to] = min_distance + e->length;
          num_paths[min_state_index][e->to] = num_paths[min_state_index][min_town_index];
        } else if (old_distance == min_distance + e->length)
          num_paths[min_state_index][e->to] += num_paths[min_state_index][min_town_index];

        num_paths[min_state_index][e->to] %= MOD;

        e = e->next;
      }
    }
  }

  printf("%d %d\n", min_distances[1][num_towns], num_paths[1][num_towns]);
}

int main() {
  static edge *adj_list[SIZE + 1] = {NULL};
  int i, num_towns, from, to, length;
  int num_stores, store_num;
  static int store[SIZE + 1] = {0};
  edge *e;

  scanf("%d", &num_towns);
  for (from = 1; from <= num_towns; from++) {
    for (to = 1; to <= num_towns; to++) {
      scanf("%d", &length);
      if (from != to) {
        e = malloc(sizeof(edge));
        e->to = to;
        e->length = length;
        e->next = adj_list[from];
        adj_list[from] = e;
      }
    }
  }

  scanf("%d", &num_stores);
  for (i = 1; i <= num_stores; i++) {
    scanf("%d", &store_num);
    store[store_num] = 1;
  }
  solve(adj_list, num_towns, store);
  return 0;
}
