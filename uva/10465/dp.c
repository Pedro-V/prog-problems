#include <stdio.h>
#include <stdlib.h>

/* Dynamic Programming (ie, bottom-up construction of the solution array via looping)
 * version of memoization.c
 */

#define MAX_T 10000
#define max(a, b) (a > b ? a : b)

void solve(int m, int n, int t) {
  int dp[MAX_T], first, second, i;
  dp[0] = 0;

  for (i = 1; i <= t; i++) {
    if (i >= m)
      first = dp[i-m];
    else
      first = -1;

    if (i >= n)
      second = dp[i-n];
    else
      second = -1;

    if (first == -1 && second == -1)
      dp[i] = -1;
    else
      dp[i] = max(first, second) + 1;
  }

  int burgers, drinking_time = 0;
  while ((burgers = dp[t - drinking_time]) == -1)
    drinking_time++;

  if (drinking_time == 0)
    printf("%d\n", burgers);
  else
    printf("%d %d\n", burgers, drinking_time);
}

int main() {
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != EOF)
    solve(m, n, t);

  return 0;
}
