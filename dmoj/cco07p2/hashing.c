/*
 * This works by defining a manual hash table for the snowflakes.
 * Each 'bin' is defined by the sum of the snowflake's length, bounded by max(N).
 *
 * Worst-case performance is the same as in the naive solution,
 * but very unlikely to happen in practice.
 */
#include <stdio.h>
#include <stdlib.h>

#define SF_LEN 6
#define SIZE 100000

int code(int snowflake[]) {
  int sum = 0;
  for (int i = 0; i < SF_LEN; i++)
    sum += snowflake[i];
  return sum % SIZE;
}

typedef struct snowflake_node {
  int snowflake[SF_LEN];
  struct snowflake_node *next;
} snowflake_node;

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
  return 0;
}

void identify_identical(snowflake_node *snowflakes[]) {
  snowflake_node *n1, *n2;
  for (int i = 0; i < SIZE; i++) {
    n1 = snowflakes[i];
    while (n1 != NULL) {
      n2 = n1->next;
      while (n2 != NULL) {
        if (are_identical(n1->snowflake, n2->snowflake)) {
          printf("Twin snowflakes found.\n");
          return;
        }
        n2 = n2->next;
      }
      n1 = n1->next;
    }
  }
  printf("No two snowflakes are alike.\n");
}

int main() {
  static snowflake_node *snowflakes[SIZE] = { NULL };
  snowflake_node *snow;
  int n, i, j, snowflake_code;
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    snow = malloc(sizeof(snowflake_node));
    for (j = 0; j < SF_LEN; j++)
      scanf("%d", &snow->snowflake[j]);
    snowflake_code = code(snow->snowflake);
    snow->next = snowflakes[snowflake_code];
    snowflakes[snowflake_code] = snow;
  }
  identify_identical(snowflakes);
}
