#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_N 10000

#define SMALL -1
#define BIG 1

void solve(int *caps, int *bottles, int n) {
  int *big_bottles, *small_bottles;
  int *big_caps, *small_caps;
  int num_small, num_big;
  int i, result, matching_bottle = -1, cap_num;

  if (n == 0)
    return;

  num_small = num_big = 0;
  // There's no clear choice for the splitting cap.
  // So just randomize to make it general.
  // We are betting on the running time, so this is a Las Vegas randomized algorithm.
  cap_num = caps[rand() % n];

  big_bottles = malloc(sizeof(int) * n);
  small_bottles = malloc(sizeof(int) * n);
  big_caps = malloc(sizeof(int) * n);
  small_caps = malloc(sizeof(int) * n);

  for (i = 0; i < n; i++) {
    printf("0 %d %d\n", cap_num, bottles[i]);
    scanf("%d", &result);
    if (result == SMALL)
      big_bottles[num_big++] = bottles[i];
    else if (result == BIG)
      small_bottles[num_small++] = bottles[i];
    else {
      matching_bottle = bottles[i];
      printf("1 %d %d\n", cap_num, matching_bottle);
    }
  }

  num_small = num_big = 0;

  for (i = 0; i < n; i++) {
    printf("0 %d %d\n", caps[i], matching_bottle);
    scanf("%d", &result);
    if (result == SMALL)
      small_caps[num_small++] = caps[i];
    else if (result == BIG)
      big_caps[num_big++] = caps[i];
  }

  solve(big_caps, big_bottles, num_big);
  solve(small_caps, small_bottles, num_small);
}

int main() {
  int n, i;
  int cap_nums[MAX_N], bottle_nums[MAX_N];
  srand((unsigned) time(NULL));
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    cap_nums[i] = bottle_nums[i] = i + 1;
  solve(cap_nums, bottle_nums, n);
}
