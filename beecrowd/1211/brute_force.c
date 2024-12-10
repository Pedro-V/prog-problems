#include <stdio.h>
#include <string.h>

#define SIZE 200

int equal_prefix_size(char *s1, char *s2, int len) {
  int size = 0, i;
  // len - 1 because we don't want to read the final '\n' fgets puts in the buffers.
  for (i = 0; i < len - 1; i++)
    if (s1[i] == s2[i])
      size++;
    else
      break;
  return size;
}

int main() {
  char prev_str[SIZE + 1], cur_str[SIZE + 1];
  int num_phones, chars_saved, i, phone_len;
  while (scanf("%d ", &num_phones) != EOF) {
    chars_saved = 0;
    fgets(prev_str, SIZE + 1, stdin);
    phone_len = strlen(prev_str);
    for (i = 1; i < num_phones; i++) {
      fgets(cur_str, SIZE + 1, stdin);
      chars_saved += equal_prefix_size(prev_str, cur_str, phone_len);
    }
    printf("%d\n", chars_saved);
  }
}
