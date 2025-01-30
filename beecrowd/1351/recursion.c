#include <stdio.h>
#include <stdlib.h>

#define N_SIZE 100000
#define M_SIZE 100
#define min(a, b) (a) < (b) ? (a) : (b)

float solve(int *list, int *products, float *prices, int n, int m, int i, int j) {
  if (i == m)
    return 0.0;
  if (j == n)
    return -1;

  int p = list[i], k;
  float min_res = N_SIZE + 1, cur_res;

  for (k = j; k < n; k++)
    if (products[k] == p) {
      cur_res = solve(list, products, prices, n, m, i+1, k+1);
      if (cur_res != -1)
        min_res = min(min_res, prices[k] + cur_res);
    }

  return min_res == N_SIZE + 1 ? -1 : min_res;
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
    res = solve(list, products, prices, n, m, 0, 0);
    if (res == -1)
      printf("Impossible\n");
    else
      printf("%.2f\n", res);
  }
}
