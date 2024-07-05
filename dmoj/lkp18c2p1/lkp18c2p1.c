#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Because N < 100, we don't need to use a more complex data structure.
 */

#define MAX_LINES 100

int min_index(int lines[], int n) {
  int idx = 0;
  for (int i = 1; i < n; i++)
    idx = lines[i] < lines[idx] ? i : idx;
  return idx;
}

void solve(int lines[], int n, int m) {
  int idx;
  for (int i = 0; i < m; i++) {
    idx = min_index(lines, n);
    printf("%d\n", lines[idx]);
    lines[idx]++;
  }
}

int main() {
  int m, n, lines[MAX_LINES];
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &lines[i]);
  solve(lines, n, m);
}
