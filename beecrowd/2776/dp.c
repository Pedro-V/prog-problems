#include <stdio.h>
#include <stdlib.h>

// This is a DP solution where, for each promotion (Q, V) and current can amount C,
// we solve the subproblem for C - Q cans, add V to it, and take the one that maximizes.
// Of course, C - Q >= 0 and C - Q must be solvable.

#define N_SIZE 1000
#define M_SIZE 2000
#define max(a, b) (a) > (b) ? (a) : (b)

int main() {
  static int dp[M_SIZE + 1], amounts[N_SIZE], values[N_SIZE];
  int n, m, i, j;

  while (scanf("%d %d", &n, &m) != EOF) {
    for (i = 0; i < n; i++)
      scanf("%d %d", &amounts[i], &values[i]);

    dp[0] = 0;
    for (i = 1; i <= m; i++) {
      dp[i] = -1;
      for (j = 0; j < n; j++)
        if (amounts[j] <= i && dp[i - amounts[j]] != -1)
          dp[i] = max(dp[i], dp[i - amounts[j]] + values[j]);
    }
    printf("%d\n", dp[m]);
  }
}
