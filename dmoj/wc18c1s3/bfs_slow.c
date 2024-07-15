#include <stdio.h>

// This is a BFS solution that suffers from too many "down" edges, being
// quadratic on the given height.

#define SIZE 1000000

// The jump is at most h, therefore 2*h or higher doesn't make sense to explore.
// And since h it at most SIZE, we do SIZE * 2.
typedef int board[SIZE * 2];
typedef int positions[SIZE * 2];

void add_position(
  int from, int to, int max_height,
  positions new_positions, int *num_new_positions,
  int itching[], board min_moves
) {
  if (to <= max_height && !itching[to] && min_moves[to] == -1) {
    min_moves[to] = min_moves[from] + 1;
    new_positions[*num_new_positions] = to;
    (*num_new_positions)++;
  }
}

void find_distances(int height, int jump, int itching[], board min_moves) {
  static positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions, from;

  for (int i = 1; i < height * 2; i++)
    min_moves[i] = -1;
  min_moves[0] = 0;
  cur_positions[0] = 0;
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;

    for (int i = 0; i < num_cur_positions; i++) {
      from = cur_positions[i];

      add_position(
        from, from + jump, height * 2 - 1,
        new_positions, &num_new_positions,
        itching, min_moves
      );

      for (int j = 1; j < from; j++)
        add_position(
          from, j, height * 2 - 1,
          new_positions, &num_new_positions,
          itching, min_moves
        );
    }

    for (int i = 0; i < num_new_positions; i++)
      cur_positions[i] = new_positions[i];
    num_cur_positions = num_new_positions;
  }
}

void solve(int height, int jump, board min_moves) {
  int best = -1;
  for (int i = height; i < height * 2; i++) {
    if (min_moves[i] != -1 && (best == -1 || min_moves[i] < best))
      best = min_moves[i];
  }
  printf("%d\n", best);
}

int main() {
  int height, jump, n, a, b;
  static int itching[SIZE * 2] = {0};
  static board min_moves;
  scanf("%d%d%d", &height, &jump, &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &a, &b);
    for (int j = a; j < b; j++)
      itching[j] = 1;
  }

  find_distances(height, jump, itching, min_moves);
  solve(height, jump, min_moves);
}
