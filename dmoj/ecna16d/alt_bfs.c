#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_LENGTH 16
#define MAX_LANGS 100
#define MAX_TRANSLATORS 4500
#define min(a, b) (a < b ? a : b)

typedef struct node {
  int id;
  int visited;
  int distance;
  int num_neighbours;
  struct node* neighbours[MAX_LANGS];
  int costs[MAX_LANGS];
} node;

// Reserve 0 for English.
typedef node *graph[MAX_LANGS + 1];

int max_str_len = 0;

char *read_word(int size) {
  char *str = malloc(size);
  int ch, len = 0;
  while ((ch = getchar()) != EOF && (ch != ' ') && (ch != '\n')) {
    str[len++] = ch;
    if (len == size) {
      size *= 2;
      str = realloc(str, size);
    }
  }

  if (len > max_str_len)
    max_str_len = len;

  str[len] = '\0';
  return str;
}

int lang_id(char* lang, char *langs[], int *num_langs) {
  int i;
  for (i = 0; i < *num_langs; i++)
    if (strcmp(lang, langs[i]) == 0)
      return i;

  langs[i] = malloc(max_str_len);
  strcpy(langs[i], lang);
  (*num_langs)++;
  return i;
}

node* new_node(char* lang, char *langs[], int *num_langs) {
  node* n = malloc(sizeof(node));
  n->id = lang_id(lang, langs, num_langs);
  n->visited = 0;
  n->distance = 0;
  n->num_neighbours = 0;
  return n;
}

void add_node(graph g, int g_len, node* n) {
  g[g_len++] = n;
}

void add_edge(graph g, char* lang1, char *lang2, char *langs[], int *len, int cost) {
  int id1 = lang_id(lang1, langs, len);
  int id2 = lang_id(lang2, langs, len);
  node *n1 = g[id1];
  n1->neighbours[n1->num_neighbours] = g[id2];
  n1->costs[n1->num_neighbours] = cost;
  n1->num_neighbours++;
}

void add_position(node *from, int to_index, node *pos[], int *num_pos, int visited[]) {
  node *to = from->neighbours[to_index];
  int distance = from->distance + 1, cost = from->costs[to_index];

  if (
    (!to->visited) ||
    to->distance > distance ||
    (to->distance == distance && visited[to->id] > cost)
  ) {
    to->visited = 1;
    to->distance = distance;
    visited[to->id] = cost;
    pos[*num_pos] = to;
    (*num_pos)++;
  }
}

void bfs(graph g, int len, int visited[]) {
  node *cur_positions[MAX_TRANSLATORS], *new_positions[MAX_TRANSLATORS];
  int num_cur_positions, num_new_positions;
  node* from;

  visited[0] = 0;
  for (int i = 1; i < len; i++)
    visited[i] = -1;

  cur_positions[0] = g[0];
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;

    for (int i = 0; i < num_cur_positions; i++) {
      from = cur_positions[i];
      for (int j = 0; j < from->num_neighbours; j++)
        add_position(from, j, new_positions, &num_new_positions, visited);
    }

    for (int i = 0; i < num_new_positions; i++)
      cur_positions[i] = new_positions[i];
    num_cur_positions = num_new_positions;
  }
}

void solve(int visited[], int len) {
  int result = 0;
  for (int i = 1; i < len; i++) {
    if (visited[i] == -1) {
      printf("Impossible\n");
      return;
    }
    result += visited[i];
  }
  printf("%d\n", result);
}

int main() {
  static int visited[MAX_LANGS + 1];
  int len, num_translators, cost;

  static char *langs[MAX_LANGS + 1] = { "English" };
  char *lang1 = "", *lang2 = "";
  int num_langs = 1;

  static graph g;
  g[0] = new_node(langs[0], langs, &num_langs);
  node *n;


  // Important ending space so that it consumes \n.
  scanf("%d %d ", &len, &num_translators);
  len++; // Account for english;

  for (int i = 1; i < len; i++) {
    lang1 = read_word(WORD_LENGTH);
    n = new_node(lang1, langs, &num_langs);
    g[n->id] = n;
  }

  lang1 = malloc(max_str_len);
  lang2 = malloc(max_str_len);

  for (int i = 0; i < num_translators; i++) {
    scanf("%s %s %d", lang1, lang2, &cost);
    add_edge(g, lang1, lang2, langs, &len, cost);
  }

  bfs(g, len, visited);
  solve(visited, len);
}
