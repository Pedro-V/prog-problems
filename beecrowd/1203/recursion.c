#include <stdio.h>

#define SIZE 100

int solve(int *arr, int n, int target, int i) {
  if (target == 0)
    return 1;
  if (i == 0)
    return 0;

  int can_solve = 0;
  for (int j = i - 1; j >= 1; j--)
    if (arr[j] <= i)
      can_solve |= solve(arr, n, target - arr[j], j);
  return can_solve;
}

int main() {
  static int degrees[SIZE + 1];
  int r, k, i, a, b;
  while (scanf("%d %d", &r, &k) != EOF) {
    for (i = 1; i <= r; i++)
      degrees[i] = 0;
    for (i = 1; i <= k; i++) {
      scanf("%d %d", &a, &b);
      degrees[a]++;
      degrees[b]++;
    }
    if (solve(degrees, r, k, r))
      printf("S\n");
    else
      printf("N\n");
  }
}
