#include <stdio.h>
#include <stdlib.h>

#define N_SIZE 100000
#define M_SIZE 100
#define min(a, b) (a) < (b) ? (a) : (b)

float solve(int *list, int *products, float *prices, int n, int m) {
  static float dp[M_SIZE + 1][N_SIZE + 1];
  int i, j;
  float x, y, p;

  for (j = 0; j <= n; j++)
    dp[m][j] = 0.0;
  for (i = 0; i < m; i++)
    dp[i][n] = -1;

  for (i = m-1; i >= 0; i--)
    for (j = n-1; j >= 0; j--) {
      x = dp[i][j+1];
      y = dp[i+1][j+1];

      if (y == -1) {
        dp[i][j] = -1;
        continue;
      }

      if (products[j] != list[i]) {
        dp[i][j] = x;
        continue;
      }

      p = prices[j] + y;
      if (x == -1)
        dp[i][j] = p;
      else
        dp[i][j] = min(x, p);
    }

  return dp[0][0];
}

int main() {
  static float prices[N_SIZE];
  static int list[M_SIZE], products[N_SIZE];
  int i, j, m, n, p;
  float res;

  while (1) {
    scanf("%d %d", &m, &n);
    if (m == 0)
      break;

    for (i = 0; i < m; i++)
      scanf("%d", &list[i]);
    for (i = 0; i < n; i++)
      scanf("%d %f", &products[i], &prices[i]);

    res = solve(list, products, prices, n, m);
    if (res == -1)
      printf("Impossible\n");
    else
      printf("%.2f\n", res);
  }
}
