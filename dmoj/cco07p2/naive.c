/*
 * Naive solution.
 * If a snowflake's len is M, are_identical() is O(M^2).
 * With N snowflakes, the entire solution is O(N^2*M^2).
 *
 */
#include <stdio.h>
#include <stdlib.h>

#define SF_LEN 6
#define SIZE 100000

/*
 * This and identical_left compare snow1 (starting at index 0)
 * with snow2 (starting at `start`).
 */
int identical_right(int snow1[], int snow2[], int start) {
  for (int i = 0; i < SF_LEN; i++) {
    if (snow1[i] != snow2[(start + i) % SF_LEN])
      return 0;
  }
  return 1;
}

int identical_left(int snow1[], int snow2[], int start) {
  int diff, idx2;
  for (int i = 0; i < SF_LEN; i++) {
    diff = start - i;
    idx2 = diff < 0 ? SF_LEN + diff : diff;
    if (snow1[i] != snow2[idx2])
      return 0;
  }
  return 1;
}

int are_identical(int snow1[], int snow2[]) {
  for (int start = 0; start < SF_LEN; start++) {
    if (
      identical_right(snow1, snow2, start) ||
      identical_left(snow1, snow2, start)
    )
      return 1;
  }
}

void identify_identical(int snowflakes[][6], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (are_identical(snowflakes[i], snowflakes[j])) {
        printf("Twin snowflakes found.\n");
        return;
      }
    }
  }
  printf("No two snowflakes are alike.\n");
}

int main() {
  static int snowflakes[SIZE][SF_LEN];
  int n, i, j;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < SF_LEN; j++)
      scanf("%d", &snowflakes[i][j]);
  identify_identical(snowflakes, n);
}
