#include <stdlib.h>

// This formulation is due to Daniel Zingaro in his book 'Algorithmic Thinking'.

#define SIZE 3001
#define square(x) ((x) * (x))

typedef int board[SIZE][SIZE];

// This function answers: Is there a rectangle with median quality rank of at most `quality`? 
// This change in question allows two things:
// - The fact that we no longer ask exact values for the median, but an upper bound, 
//   means we can drop the sorting requirement.
// - It also means we can avoid linearly-computing if a rectangle's median is
//   within the upper bound by using dynamic programming to efficiently
//   answer 2-dimensional range sum queries.
int feasible(int quality, int r, int c, int h, int w, board q) {
  static board zero_one;
  static int sum[SIZE + 1][SIZE + 1];
  int i, j;
  int top_row, left_col, bottom_row, right_col;
  int total;

  // We use the 0s and 1s to check the upper bound of a given rectangle's median.
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      zero_one[i][j] = q[i][j] <= quality ? -1 : 1;

  // Use DP to build a prefix sum array that enables answers
  // to 2-dimensional range sum queries in O(1).
  // sum[i][j] gives the sum of 0s and 1s of the rectangle with top left
  // at (0, 0) and bottom right at (i, j).
  for (i = 0; i <= c; i++)
    sum[0][i] = 0;
  for (i = 0; i <= r; i++)
    sum[i][0] = 0;
  for (i = 1; i <= r; i++)  // Index at 1 to avoid bounds-checking.
    for (j = 1; j <= c; j++)
      sum[i][j] = zero_one[i - 1][j - 1] + sum[i -1][j] + sum[i][j - 1] - sum[i - 1][j - 1];

  // Check all rectangles. Note that we start from index 1 because of how `sum`
  // is laid out.
  for (top_row = 1; top_row <= r - h + 1; top_row++)
    for (left_col = 1; left_col <= c - w + 1; left_col++) {
      bottom_row = top_row + h - 1;
      right_col = left_col + w - 1;
      // Find if this rectangle's median is within the upper bound.
      // We don't explicitly calculate the median, just do an O(1) range sum query.
      total = sum[bottom_row][right_col] - sum[top_row - 1][right_col] -
              sum[bottom_row][left_col - 1] + sum[top_row - 1][left_col - 1];
      if (total <= 0)
        return 1;
    }
  return 0;
}

int rectangle(int r, int c, int h, int w, board q) {
  int low, high, mid;
  // Invariant: anything <= low is unfeasible, and anything >= high if feasible.
  low = 0;
  high =  r * c + 1;
  while (high - low > 1) {
    mid = (low + high) / 2;
    if (feasible(mid, r, c, h, w, q))
      high = mid;
    else
      low = mid;
  }

  return high;
}
