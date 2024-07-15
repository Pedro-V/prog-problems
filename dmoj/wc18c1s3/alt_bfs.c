#include <stdio.h>

// A solution that uses less arrays than `bfs.c` by putting itching info on the
// same min_moves solution array, but there are some WA cases.
// TODO: Discover in which cases this fails.

#define SIZE 1000000
#define ITCHING -2

void add_movement(
  int from, int to, int new_positions[], int *num_new_positions,
  int min_moves[]
) {
  if (to < SIZE && min_moves[to] == -1) {
    min_moves[to] = min_moves[from] + 1;
    new_positions[*num_new_positions] = to;
    (*num_new_positions)++;
  }
}

void find_distances(int height, int jump, int min_moves[]) {
  static int cur_positions[SIZE * 2], new_positions[SIZE * 2];
  int num_cur_positions = 1, num_new_positions;
  int from, to, distance;

  cur_positions[0] = 0;

  while (num_cur_positions > 0) {
    num_new_positions = 0;

    for (int i = 0; i < num_cur_positions; i++) {
      from = cur_positions[i];

      to = from + jump;
      add_movement(from, to, new_positions, &num_new_positions, min_moves);

      to = from - 1;
      distance = min_moves[from] + 1;
      while (to > 0 && (min_moves[to] < 0 || min_moves[to] > distance)) {
        if (min_moves[to] != ITCHING)
          add_movement(from, to, new_positions, &num_new_positions, min_moves);
        to--;
      }
    }

    for (int i = 0; i < num_new_positions; i++)
      cur_positions[i] = new_positions[i];
    num_cur_positions = num_new_positions;
  }
}

void solve(int height, int min_moves[]) {
  int best = -1;
  for (int i = height; i < height * 2; i++) {
    if (min_moves[i] != -1 && (best == -1 || min_moves[i] < best))
      best = min_moves[i];
  }
  printf("%d\n", best);
}

int main() {
  int height, jump, n, a, b;
  static int min_moves[SIZE * 2];

  scanf("%d %d %d", &height, &jump, &n);

  min_moves[0] = 0;
  for (int i = 1; i < height * 2; i++)
    min_moves[i] = -1;

  while (n--) {
    scanf("%d %d", &a, &b);
    for (int j = a; j <= b; j++)
      min_moves[j] = ITCHING;
  }

  find_distances(height, jump, min_moves);
  solve(height, min_moves);
}
