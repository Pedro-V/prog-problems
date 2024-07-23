/*
 * Due to the problem's spec, reading from the stdin/stdout isn't included in
 * the main file.
 *
 */
#include <stdio.h>

// Choose which source to use:
#include "bin_search.c"

int main() {
  int r, c, h, w;
  static board q;

  scanf("%d%d%d%d", &r, &c, &h, &w);
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      scanf("%d", &q[i][j]);

  printf("%d\n", rectangle(r, c, h, w, q));

  return 0;
}
