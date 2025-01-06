#include <stdlib.h>
#include <stdio.h>

#define SIZE 10000
// spc = Spaceship operator. Similar to <=> in PHP.
#define spc(a, b) (a) < (b) ? -1 : 1

int m;

int cmp(const void *a, const void *b) {
  int x, y;
  x = *(int *)a;
  y = *(int *)b;

  if (x % m != y % m) 
    return spc(x % m, y % m);
  if (x % 2 == 0 && y % 2 == 0)
    return spc(x, y);
  if (x % 2 != 0 && y % 2 != 0)
    return spc(-x, -y);
  return spc(x % 2 == 0, y % 2 == 0);
}

int main() {
  int n, i;
  static int nums[SIZE];

  while (1) {
    scanf("%d %d", &n, &m);
    if (n == 0 && m == 0)
      break;

    for (i = 0; i < n; i++)
      scanf("%d", &nums[i]);
    qsort(nums, n, sizeof(int), cmp);

    printf("%d %d\n", n, m);
    for (i = 0; i < n; i++)
      printf("%d\n", nums[i]);
  }

  printf("0 0\n");
}
