#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000
#define min(a, b) (a < b ? a : b)

// This is a memoization solution where the subproblems are defined by finding the
// minimal cost of going from square 2 to exactly square i, with exactly a jump of j.
int solve_ij(int cost[], int n, int i, int j, int memo[MAX_N + 1][MAX_N + 1]) {
  if (memo[i][j] != -2)
    return memo[i][j];

  // Base case is getting to square 2 with a jump of 1. 
  // This jump of 1 is the required initial jump from the problem spec.
  if (i == 2 && j == 1) {
    memo[i][j] = cost[2];
    return memo[i][j];
  }

  // Two possible subproblems:
  int first, second;

  // 1. Getting to square i with a jump to the right.
  if (i - j >= 1 && j >= 2)
    first = solve_ij(cost, n, i - j, j - 1, memo);
  else
    first = -1;

  // 2. Getting to square i with a jump to the left.
  if (i + j <= n)
    second = solve_ij(cost, n, i + j, j, memo);
  else
    second = -1;

  if (first == -1 && second == -1)
    memo[i][j] = -1;
  else if (second == -1)
    memo[i][j] = first + cost[i];
  else if (first == -1)
    memo[i][j] = second + cost[i];
  else
    memo[i][j] = min(first, second) + cost[i];

  return memo[i][j];
}

int solve(int cost[], int n) {
  int best, result;
  static int memo[MAX_N + 1][MAX_N + 1];
  for (int i = 1; i <= MAX_N; i++)
    for (int j = 1; j <= MAX_N; j++)
      memo[i][j] = -2;

  best = (int)INFINITY;
  for (int j = 1; j <= n; j++) {
    result = solve_ij(cost, n, n, j, memo);
    if (result != -1)
      best = min(best, result);
  }

  return best;
}

int main() {
  int n;
  int cost[MAX_N + 1];

  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &cost[i]);

  printf("%d\n", solve(cost, n));
}
