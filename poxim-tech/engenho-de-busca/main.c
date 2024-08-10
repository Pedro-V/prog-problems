#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATTERN_LEN 100

FILE *input, *output;

typedef struct {
  int used_cap;
  char **patterns;
} server;

int checksum(char str[]) {
  int i = 0, result = 0;
  while (str[i] != '\0') {
    if (str[i] != ' ') result ^= str[i];
    i++;
  }
  return result;
}

int double_hash(char str[], int i, int len, int cs) {
  return (unsigned int)(7919 * cs + i * (104279 * cs + 123)) % len;
}

void print_patterns(server s, int index) {
  fprintf(output, "[S%d]", index);
  for (int i = 0; i < s.used_cap; i++) {
    fprintf(output, " %s", s.patterns[i]);
    if (i == s.used_cap - 1)
      putc('\n', output);
    else
      putc(',', output);
  }
}

void add_to_server(server *s, char str[]) {
  s->patterns[s->used_cap] = malloc(sizeof(char) * (PATTERN_LEN + 1));
  strcpy(s->patterns[s->used_cap++], str);
}

void find_server(char str[], server *servers, int num_servers, int max_cap) {
  int i, first_index, final_index;
  int cs = checksum(str);

  first_index = double_hash(str, 0, num_servers, cs);

  if (!(servers[first_index].used_cap < max_cap)) {
    i = 1;
    do {
      final_index = double_hash(str, i++, num_servers, cs);
    } while (servers[final_index].used_cap == max_cap);
    fprintf(output, "S%d->S%d\n", first_index, final_index);
  } else {
    final_index = first_index;
  }

  add_to_server(&servers[final_index], str);
  print_patterns(servers[final_index], final_index);
}

int main(int argc, char **argv) {
  int i, num_servers, max_cap, num_reqs, num_patterns;
  server *servers;
  char pattern[100];

  input = fopen(argv[1], "r");
  output = fopen(argv[2], "w");
  if (!input) {
    printf("Error opening files.\n");
    exit(EXIT_FAILURE);
  }

  fscanf(input, "%d%d%d", &num_servers, &max_cap, &num_reqs);
  servers = calloc(num_servers, sizeof(server));
  for (i = 0; i < num_servers; i++)
    servers[i].patterns = malloc(sizeof(char *) * max_cap);

  for (i = 0; i < num_reqs; i++) {
    fscanf(input, "%d %[^\n]", &num_patterns, pattern);
    find_server(pattern, servers, num_servers, max_cap);
  }
  return 0;
}
