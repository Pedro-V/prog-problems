#include <stdlib.h>

#define SIZE 3001
#define square(x) ((x) * (x))

typedef int board[SIZE][SIZE];

int compare(const void *v1, const void *v2) {
  int a = *(const int *)v1;
  int b = *(const int *)v2;
  return a - b;
}

int median(int top_row, int left_col, int bottom_row, int right_col, board q) {
  static int cur_rectangle[square(SIZE)];
  int i, j, num_cur_rectangle;
  num_cur_rectangle = 0;
  for (i = top_row; i <= bottom_row; i++)
    for (j = left_col; j <= right_col; j++) {
      cur_rectangle[num_cur_rectangle] = q[i][j];
      num_cur_rectangle++;
    }

  qsort(cur_rectangle, num_cur_rectangle, sizeof(int), compare);
  return cur_rectangle[num_cur_rectangle / 2];
}

int rectangle(int r, int c, int h, int w, board q) {
  int top_row, left_col, bottom_row, right_col;
  int cur_median, min_median = -1;

  for (top_row = 0; top_row <= r - h; top_row++)
    for (left_col = 0; left_col <= c - w; left_col++) {
      bottom_row = top_row + h - 1;
      right_col = left_col + w - 1;
      cur_median = median(top_row, left_col, bottom_row, right_col, q);
      if (min_median == -1 || cur_median < min_median)
        min_median = cur_median;
    }

  return min_median;
}
