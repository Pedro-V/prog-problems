#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define SIZE 100
#define min(a, b) (a < b ? a : b)

typedef struct edge {
  int to, cost;
  struct edge *next;
} edge;

/*
 * This is a Dijkstra implementation similar to `dijkstra_slower.c`,
 * but this reverses the edges in the input graph, which allows one to call
 * Djikstra's algorithm on the exit cell and and the just run over the distances
 * array to check for the solution.
*/


/* Populates the single-source shortest paths array (min_times) for the exit cell. */
void find_min_times(edge *adj_list[], int min_times[], int num_cells, int exit_cell) {
  int visited[SIZE + 1] = { 0 };
  int min_time_idx, i, j, min_time, found;
  edge *e;

  for (i = 1; i <= num_cells; i++) {
    visited[i] = 0;
    min_times[i] = -1;
  }
  min_times[exit_cell] = 0;

  for (i = 1; i <= num_cells; i++) {
    /* Find the next vertex */
    min_time = -1;
    found = 0;
    for (j = 1; j <= num_cells; j++) {
      if ((!visited[j] && min_times[j] >= 0) &&
          (min_time == -1 || min_times[j] < min_time)) {
        min_time = min_times[j];
        min_time_idx = j;
        found = 1;
      }
    }

    /* The input graph may not be connected. In that case, we don't find the
     * next vertex because it isn't eligible in the previous search. */
    if (!found)
      break;

    e = adj_list[min_time_idx];
    while (e) {
      if (min_times[e->to] == -1)
        min_times[e->to] = min_times[min_time_idx] + e->cost;
      else
        min_times[e->to] = min(min_times[e->to], min_times[min_time_idx] + e->cost);
      e = e->next;
    }

    visited[min_time_idx] = 1;
  }
}

int main() {
  static edge *adj_list[SIZE + 1] = {NULL};
  int min_times[SIZE + 1];
  edge *e;
  int num_cases, num_cells, num_passages, limit, exit_cell;
  int i, case_num, from, to, cost, result;

  scanf("%d", &num_cases);
  for (case_num = 1; case_num <= num_cases; case_num++) {
    scanf("%d %d %d %d", &num_cells, &exit_cell, &limit, &num_passages);

    for (i = 1; i <= num_cells; i++)
      adj_list[i] = NULL;

    for (i = 0; i < num_passages; i++) {
      scanf("%d %d %d", &from, &to, &cost);

      /* Reverses the graph. Compare with `dijkstra_slower.c` */
      e = malloc(sizeof(edge));
      e->to = from;
      e->cost = cost;
      e->next = adj_list[to];
      adj_list[to] = e;
    }

    result = 0;
    find_min_times(adj_list, min_times, num_cells, exit_cell);
    for (i = 1; i <= num_cells; i++)
      if (min_times[i] >= 0 && min_times[i] <= limit)
        result++;

    printf("%d\n", result);
    if (case_num < num_cases)
      printf("\n");
  }

  return 0;
}

