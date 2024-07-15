#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LANGS 101
#define WORD_LENGTH 16

char *read_word(int size) {
  char ch, *str = malloc(size);
  int len = 0;
  while ((ch = getchar()) != EOF && ch != ' ' && ch != '\n') {
    str[len++] = ch;
    if (len == size) {
      size *= 2;
      str = realloc(str, size);
    }
  }
  str[len] = '\0';
  return str;
}

typedef struct edge {
  int to_lang, cost;
  struct edge *next;
} edge;

typedef int board[MAX_LANGS];
typedef int positions[MAX_LANGS];

int find_lang(char *langs[], char *lang) {
  int i = 0;
  while (strcmp(langs[i], lang) != 0)
    i++;
  return i;
}

void add_position(
  int from_lang, int to_lang,
  positions new_positions, int *num_new_positions,
  board min_moves
) {
  if (min_moves[to_lang] == -1) {
    min_moves[to_lang] = min_moves[from_lang] + 1;
    new_positions[*num_new_positions] = to_lang;
    (*num_new_positions)++;
  }
}

void bfs(edge *adj_list[], int num_langs, board min_costs) {
  static board min_moves;
  static positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions;
  int from_lang, added_lang, best;
  edge *e;

  for (int i = 0; i < num_langs; i++)
    min_costs[i] = min_moves[i] = -1;
  min_moves[0] = cur_positions[0] = 0;
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;

    for (int i = 0; i < num_cur_positions; i++) {
      from_lang = cur_positions[i];
      e = adj_list[from_lang];

      while (e) {
        add_position(from_lang, e->to_lang, new_positions, &num_new_positions, min_moves);
        e = e->next;
      }
    }

    for (int i = 0; i < num_new_positions; i++) {
      added_lang = new_positions[i];
      e = adj_list[added_lang];
      best = -1;

      while (e) {
        // Filter only the neighbors to this added_lang that have a distance of
        // one less than it. That is, were added in the current BFS round.
        if (min_moves[e->to_lang] + 1 == min_moves[added_lang] &&
            (best == -1 || e->cost < best))
          best = e->cost;
        e = e->next;
      }
      min_costs[added_lang] = best;
    }

    for (int i = 0; i < num_new_positions; i++)
      cur_positions[i] = new_positions[i];
    num_cur_positions = num_new_positions;
  }
}

void solve(int num_langs, board min_costs) {
  int total = 0;
  for (int i = 1; i < num_langs; i++) {
    if (min_costs[i] == -1) { printf("Impossible\n"); return; }
    else total += min_costs[i];
  }
  printf("%d\n", total);
}

int main() {
  static edge *adj_list[MAX_LANGS] = {NULL};
  static char *lang_names[MAX_LANGS] = {"English"};
  int num_targets, num_translators, cost, from_index, to_index;
  char *from_lang, *to_lang;
  edge *e;
  static board min_costs;

  // Important ending space for consuming whitespace.
  scanf("%d%d ", &num_targets, &num_translators);
  for (int i = 1; i <= num_targets; i++)
    lang_names[i] = read_word(WORD_LENGTH);

  for (int i = 0; i < num_translators; i++) {
    from_lang = read_word(WORD_LENGTH);
    to_lang = read_word(WORD_LENGTH);
    scanf("%d ", &cost);

    from_index = find_lang(lang_names, from_lang);
    to_index = find_lang(lang_names, to_lang);

    // Add two edges because it's an undirected weighted graph.
    e = malloc(sizeof(edge));
    e->to_lang = to_index;
    e->cost = cost;
    e->next = adj_list[from_index];
    adj_list[from_index] = e;

    e = malloc(sizeof(edge));
    e->to_lang = from_index;
    e->cost = cost;
    e->next = adj_list[to_index];
    adj_list[to_index] = e;
  }

  bfs(adj_list, num_targets + 1, min_costs);
  solve(num_targets + 1, min_costs);
}
