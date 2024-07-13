#include <stdio.h>

#define MAX_ROWS 99
#define MAX_COLS 99
#define NUM_MOVES 8

int move_difs[2][NUM_MOVES] = {
  { 1, 1, -1, -1, 2, 2, -2, -2 },
  { 2, -2, 2, -2, 1, -1, 1, -1 }
};

typedef struct {
  int row, col;
} position;

typedef int board[MAX_ROWS + 1][MAX_COLS + 1];
typedef position positions[MAX_ROWS * MAX_COLS];

void add_position(
  int from_row, int from_col,
  int to_row, int to_col,
  int num_rows, int num_cols,
  positions new_positions, int *num_new_positions,
  board min_moves
) {
  position new_position;

  if (min_moves[to_row][to_col] == -1 &&
      to_row >= 1 && to_col >= 1 &&
      to_row <= num_rows && to_col <= num_cols) {
    min_moves[to_row][to_col] = 1 + min_moves[from_row][from_col];
    new_position = (position){ to_row, to_col };
    new_positions[*num_new_positions] = new_position;
    (*num_new_positions)++;
  }
}


// Applies BFS to search the minimum number of moves required to move from the
// given knight_row, knight_col to all other positions.
void find_distance(
  int knight_row, int knight_col,
  int num_rows, int num_cols,
  board min_moves
) {
  positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions;
  int from_row, from_col;
  int dy, dx;

  for (int i = 1; i <= num_rows; i++)
    for (int j = 1; j <= num_cols; j++)
      min_moves[i][j] = -1;

  min_moves[knight_row][knight_col] = 0;
  cur_positions[0] = (position){ knight_row, knight_col };
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;
    for (int i = 0; i < num_cur_positions; i++) {
      from_row = cur_positions[i].row;
      from_col = cur_positions[i].col;

      for (int j = 0; j < NUM_MOVES; j++) {
        dx = move_difs[0][j];
        dy = move_difs[1][j];
        add_position(from_row, from_col, from_row + dx, from_col + dy,
                    num_rows, num_cols, new_positions,
                    &num_new_positions, min_moves);
      }
    }

    num_cur_positions = num_new_positions;
    for (int i = 0; i < num_cur_positions; i++)
      cur_positions[i] = new_positions[i];
  }
}

void solve(
  int pawn_row, int pawn_col,
  int knight_row, int knight_col,
  int num_rows, int num_cols
) {
  int cur_pawn_row, num_moves, knight_takes;
  board min_moves;

  find_distance(knight_row, knight_col, num_rows, num_cols, min_moves);

  cur_pawn_row = pawn_row, num_moves = 0;
  while (cur_pawn_row < num_rows) {
    knight_takes = min_moves[cur_pawn_row][pawn_col];

    // The last condition accounts for the fact that if the knight reaches a
    // square in a minimum of m moves, it can reach it in m + 2 moves, m + 4, etc,
    // by simply going to the previous square and returning.
    if (knight_takes >= 0 && num_moves >= knight_takes &&
        (num_moves - knight_takes) % 2 == 0) {
      printf("Win in %d knight move(s).\n", num_moves);
      return;
    }

    cur_pawn_row++;
    num_moves++;
  }

  cur_pawn_row = pawn_row, num_moves = 0;
  while (cur_pawn_row < num_rows) {
    knight_takes = min_moves[cur_pawn_row + 1][pawn_col];

    if (knight_takes >= 0 && num_moves >= knight_takes &&
        (num_moves - knight_takes) % 2 == 0) {
      printf("Stalemate in %d knight move(s).\n", num_moves);
      return;
    }

    cur_pawn_row++;
    num_moves++;
  }

  printf("Loss in %d knight move(s).\n", num_rows - pawn_row - 1);
}

int main() {
  int num_cases, num_rows, num_cols, pawn_row, pawn_col, knight_row, knight_col;
  scanf("%d", &num_cases);
  for (int i = 0; i < num_cases; i++) {
    scanf("%d%d", &num_rows, &num_cols);
    scanf("%d%d", &pawn_row, &pawn_col);
    scanf("%d%d", &knight_row, &knight_col);
    solve(pawn_row, pawn_col, knight_row, knight_col, num_rows, num_cols);
  }
}
