#include <stdio.h>

#define MAX_N 1000
#define min(a, b) (a < b ? a : b)

// Memoization solution, similar to memo.c, but with a forward formulation.
// Some find forward formulations more natural for certain problems.

// This is a memoization solution where the subproblems are defined as finding
// the minimal cost of going from square i to exactly square n, given that we
// reached i with a jump of exactly j.
int solve_ij(int cost[], int n, int i, int j, int memo[MAX_N + 1][MAX_N + 1]) {
  if (memo[i][j] != -2)
    return memo[i][j];

  // Base case is when i = n and j is anything.
  if (i == n) {
    memo[i][j] = 0;
    return memo[i][j];
  }

  // We have two possible subproblems:
  int first, second;

  // 1. We make jump j+1 to the right next.
  if (i + j + 1 <= n)
    first = solve_ij(cost, n, i + j + 1, j + 1, memo);
  else
    first = -1;

  // 2. We make a jump j to the left.
  if (i - j >= 1)
    second = solve_ij(cost, n, i - j, j, memo);
  else
    second = -1;

  if (first == -1 && second == -1)
    memo[i][j] = -1;
  else if (first == -1)
    memo[i][j] = second + cost[i - j];
  else if (second == -1)
    memo[i][j] = first + cost[i + j + 1];
  else
    memo[i][j] = min(first + cost[i + j + 1], second + cost[i - j]);

  return memo[i][j];
}

int solve(int cost[], int n) {
  static int memo[MAX_N + 1][MAX_N + 1];

  for (int i = 1; i <= MAX_N; i++)
    for (int j = 1; j <= MAX_N; j++)
      memo[i][j] = -2;

  // We account for the mandatory initial jump.
  int result = cost[2] + solve_ij(cost, n, 2, 1, memo);
  return result;
}

int main() {
  int n;
  int cost[MAX_N + 1];

  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &cost[i]);

  printf("%d\n", solve(cost, n));
}
