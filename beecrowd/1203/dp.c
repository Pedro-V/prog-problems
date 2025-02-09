#include <stdio.h>

#define R_SIZE 100
// With R at most 100, K is at most 4950.
#define K_SIZE 4950

int solve(int *arr, int n, int target) {
  static int dp[K_SIZE][R_SIZE];
  int i, j;

  for (j = 0; j <= n; j++)
    dp[0][j] = 1;
  for (i = 1; i <= target; i++)
    dp[i][0] = 0;

  for (i = 1; i <= target; i++)
    for (j = 1; j <= n; j++)
      dp[i][j] = dp[i][j-1] || (arr[j] <= i && dp[i - arr[j]][j-1]);

  return dp[target][n];
}

int main() {
  static int degrees[R_SIZE + 1];
  int r, k, i, a, b;
  while (scanf("%d %d", &r, &k) != EOF) {
    for (i = 1; i <= r; i++)
      degrees[i] = 0;
    for (i = 1; i <= k; i++) {
      scanf("%d %d", &a, &b);
      degrees[a]++;
      degrees[b]++;
    }
    if (solve(degrees, r, k))
      printf("S\n");
    else
      printf("N\n");
  }
}
