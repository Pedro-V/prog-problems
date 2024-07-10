#include <stdio.h>
#include <stdlib.h>

// Recursive solution.
// Since the formulation is not very obvious at first, this is heavily
// commented.

#define max(a, b) (a > b ? a : b)

// Helper function that, if there's a way of filling exactly t minutes with
// burgers, then it return the maximum number of burgers Homer can eat in exactly t minutes.
// Otherwise, return -1.
int solve_t(int m, int n, int t) {
  // Base case.
  if (t == 0)
    return 0;

  // Possibility 1: The last burger is an m burger.
  int first;
  if (t >= m)
    first = solve_t(m, n, t - m);
  else
    first = -1;

  // Poss. 2: The last burger is an n burger.
  int second;
  if (t >= n)
    second = solve_t(m, n, t - n);
  else
    second = -1;

  // Poss. 3: The last burger isn't either an m or n burger.
  // Therefore, we can't fill exactly t minutes with burgers alone.
  if (first == -1 && second == -1)
    return -1;

  // Poss. 4: Either one or both burgers can be the last one.
  // Just choose the one that maximizes the overall number of burgers for t.
  return max(first, second) + 1;
}

// Try to solve exactly for t, t-1, t-2... t-k.. 0.
// After finding an exact solution for some t-k, we know:
// - The maximum number of burgers we can eat for t-k.
// - The amount of minutes spent drinking beer (k).
void solve(int m, int n, int t) {
  int solution, min_drinking = 0;

  while ((solution = solve_t(m, n, t - min_drinking)) == -1)
    min_drinking++;

  if (min_drinking == 0)
    printf("%d\n", solution);
  else
    printf("%d %d\n", solution, min_drinking);
}

int main() {
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != EOF)
    solve(m, n, t);
}
