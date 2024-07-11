#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000
#define min(a, b) (a < b ? a : b)

// This is a DP forward solution, similtar to `memo_forward.c`.
int solve(int cost[], int n) {
  static int dp[MAX_N + 1][MAX_N + 1];
  int first, second;

  for (int j = 1; j <= n; j++)
    dp[n][j] = 0;

  // This DP forward is interesting because the solution order is
  // non-conventional.
  // Here, we solve from the n-th column, to the 1st, and inside them, from the 1st row to the nth.
  for (int j = n; j >= 1; j--) {
    for (int i = 1; i < n; i++) {

      if (i + j + 1 <= n)
        first = dp[i + j + 1][j + 1];
      else
        first = -1;

      if (i - j >= 1)
        second = dp[i - j][j];
      else
        second = -1;

      if (first == -1 && second == -1)
        dp[i][j] = -1;
      else if (first == -1)
        dp[i][j] = second + cost[i - j];
      else if (second == -1)
        dp[i][j] = first + cost[i + j + 1];
      else
        dp[i][j] = min(first + cost[i + j + 1], second + cost[i - j]);
    }
  }

  return cost[2] + dp[2][1];
}

int main() {
  int n;
  int cost[MAX_N + 1];

  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &cost[i]);

  printf("%d\n", solve(cost, n));
}
