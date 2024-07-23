#include <stdio.h>
#include <stdlib.h>

#define SIZE 50000

/*
 * Given a minimum distance `d`, can we use up to `num_removals` 
 * to achieve a minimum distance >= d?
 * If so, then d is a feasible solutions to this.
 * We use a greedy strategy to determine feasability.
 */
int feasible(int rocks[], int num_rocks, int d, int allowed_removals) {
  int removals = 0, dist, curr, prev;

  if (d > rocks[num_rocks - 1])
    return 0;

  for (curr = 1, prev = 0; curr < num_rocks; curr++) {
    dist = rocks[curr] - rocks[prev];
    if (dist >= d)
      prev = curr;
    else
      removals++;
  }
  return removals <= allowed_removals;
}

void solve(int rocks[], int num_rocks, int allowed_removals) {
  int low, high, mid;
  low = 0;
  /*
   * Our invariant assumes high is always infeasible and low is always feasible.
   * In cases where a jump equal to the river's length is feasible (sample5.input), we should
   * start high with an infeasible value, which length + 1 is guaranteed to be.
   */
  high = rocks[num_rocks - 1] + 1;
  while (high - low > 1) {
    mid = (low + high) / 2;

    if (feasible(rocks, num_rocks, mid, allowed_removals))
      low = mid;
    else
      high = mid;
  }
  printf("%d\n", low);
}

int compare(const void *a, const void *b) {
  int n1 = *(int *)a, n2 = *(int *)b;
  return n1 - n2;
}

int main() {
  int rocks[SIZE + 2], num_rocks;
  int i, len, n, allowed_removals;

  scanf("%d %d %d", &len, &n, &allowed_removals);
  num_rocks = n + 2;
  rocks[0] = 0;
  rocks[1] = len;
  for (i = 0; i < n; i++)
    scanf("%d", &rocks[i + 2]);
  qsort(rocks, num_rocks, sizeof(int), compare);

  solve(rocks, num_rocks, allowed_removals);

  return 0;
}
