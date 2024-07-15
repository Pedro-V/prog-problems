#include <stdio.h>

// This is a BFS that doesn't map the problem to the graph, which allow for
// reducing how many edges there are, speeding the solution in `bfs_slow.c`.
// We basically keep two "ropes", where the second one the moves to go down are
// free. The formulation is due to section 5.2 of Algorithmic Thinking by Daniel Zingaro.
// Aka 0-1 BFS.

#define SIZE 1000000

typedef struct {
  int height, state;  // State keeps track of in which rope this position is.
} position;

typedef int board[2][SIZE * 2];
typedef position positions[SIZE * 4];

// Goes up on rope 0.
void add_position_up(
  int from, int to, int max_height,
  positions pos, int *num_pos,
  int itching[], board min_moves
) {
  if (to <= max_height && !itching[to]) {
    min_moves[0][to] = 1 + min_moves[0][from];
    pos[*num_pos] = (position){ to, 0 };
    (*num_pos)++;
  }
}

// Goes down on rope 1.
void add_position_down(int from, int to, positions pos, int *num_pos, board min_moves) {
  int distance = min_moves[1][from];
  if (to >= 0 && (min_moves[1][to] == -1 || min_moves[1][to] > distance)) {
    min_moves[1][to] = distance;
    pos[*num_pos] = (position){ to, 1 };
    (*num_pos)++;
  }
}

// Switches from rope 0 to rope 1.
void add_position_01(int from, positions pos, int *num_pos, board min_moves) {
  int distance = min_moves[0][from] + 1;
  if (min_moves[1][from] == -1 || min_moves[1][from] > distance) {
    min_moves[1][from] = distance;
    pos[*num_pos] = (position){ from, 1 };
    (*num_pos)++;
  }
}

// Switches from rope 0 to rope 1.
void add_position_10(int from, positions pos, int *num_pos, int itching[], board min_moves) {
  int distance = min_moves[1][from];
  if (
    !itching[from] && 
    (min_moves[0][from] == -1 || min_moves[0][from] > distance)
  ) {
    min_moves[0][from] = distance;
    pos[*num_pos] = (position){ from, 0 };
    (*num_pos)++;
  }
}

void find_distances(int height, int jump, int itching[], board min_moves) {
  static positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions;
  int from_height, from_state;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < height * 2; j++)
      min_moves[i][j] = -1;

  min_moves[0][0] = 0;
  cur_positions[0] = (position){ 0, 0 };
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;

    for (int i = 0; i < num_cur_positions; i++) {
      from_height = cur_positions[i].height;
      from_state = cur_positions[i].state;

      if (from_state == 0) {
        add_position_up(
          from_height, from_height + jump, height * 2 - 1,
          new_positions, &num_new_positions,
          itching, min_moves
        );
        add_position_01(from_height, new_positions, &num_new_positions, min_moves);
      } else {
        add_position_down(
          from_height, from_height - 1, cur_positions, &num_cur_positions, min_moves
        );
        add_position_10(from_height, cur_positions, &num_cur_positions, itching, min_moves);
      }
    }

    for (int i = 0; i < num_new_positions; i++)
      cur_positions[i] = new_positions[i];
    num_cur_positions = num_new_positions;
  }
}

void solve(int height, board min_moves) {
  int best = -1;
  for (int i = height; i < height * 2; i++) {
    if (min_moves[0][i] != -1 && (best == -1 || min_moves[0][i] < best))
      best = min_moves[0][i];
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
    for (int j = a; j <= b; j++)
      itching[j] = 1;
  }

  find_distances(height, jump, itching, min_moves);
  solve(height, min_moves);
}
