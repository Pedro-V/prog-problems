#include <stdio.h>
#include <stdlib.h>

// Memoized version of the previous recursive formulation.

#define MAX_T 10000
#define NOT_SOLVED (-2)
#define max(a, b) (a > b ? a : b)

int solve_t(int m, int n, int t, int memo[]) {
  if (memo[t] != NOT_SOLVED)
    return memo[t];

  if (t == 0) {
    memo[t] = 0;
    return memo[t];
  }

  int first;
  if (t >= m)
    first = solve_t(m, n, t - m, memo);
  else
    first = -1;

  int second;
  if (t >= n)
    second = solve_t(m, n, t - n, memo);
  else
    second = -1;

  if (first == -1 && second == -1) {
    memo[t] = -1;
    return memo[t];
  }
  memo[t] = max(first, second) + 1;
  return memo[t];
}


void solve(int m, int n, int t) {
  int solution, min_drinking = 0;

  int memo[MAX_T];
  for (int i = 0; i <= t; i++) {
    memo[i] = NOT_SOLVED;
  }

  while ((solution = solve_t(m, n, t - min_drinking, memo)) == -1)
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

