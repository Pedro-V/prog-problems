#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100000
#define STRLEN 200

int len_common_prefix(char *s1, char *s2) {
  int i = 0;
  while (s1[i] == s2[i]) i++;
  return i;
}

int my_strcmp(const void *a, const void *b) {
  return strcmp((const char *)a, (const char *)b);
}

int main() {
  static char phones[SIZE][STRLEN + 1];
  int num_phones, chars_saved, i;
  while (scanf("%d ", &num_phones) != EOF) {
    for (i = 0; i < num_phones; i++)
      scanf("%s", phones[i]);
    qsort(phones, num_phones, STRLEN + 1, my_strcmp);
    chars_saved = 0;
    for (i = 1; i < num_phones; i++)
      chars_saved += len_common_prefix(phones[i-1], phones[i]);
    printf("%d\n", chars_saved);
  }
}
