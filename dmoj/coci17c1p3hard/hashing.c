/*
 * For each added password:
 * - generate all unique substrings from it.
 *   this ain't expensive because each password has at most 10 characters,
 *   therefore we have a maximum of 55 substrings generated for it
 * - Put them on a chained hash table.
 * - Increment the hashtable entry for them.
 *
 * On query operations, just check the hash table.
 * This solution is by Daniel Zingaro (Algorithmic Thinking, 2nd Ed).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

// One-at-a-time. Generic hash function from: https://burtleburtle.net/bob/hash/doobs.html
unsigned long ooat (char *key, unsigned long len, unsigned long bits) {
  unsigned long hash, i;
  for (hash = 0, i = 0; i < len; i++) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash & hashmask(bits);
}

#define MAX_LEN 10
#define MAX_SUBSTRS 55

typedef struct password_node {
  char password[MAX_LEN + 1];
  int total;
  struct password_node *next;
} password_node;

#define NUM_BITS 20
password_node *in_hash_table(password_node *hash_table[], char *find) {
  unsigned password_code;
  password_node *password_ptr;
  password_code = ooat(find, strlen(find), NUM_BITS);
  password_ptr = hash_table[password_code];
  while (password_ptr) {
    if (strcmp(password_ptr->password, find) == 0)
      return password_ptr;
    password_ptr = password_ptr->next;
  }
  return NULL;
}

void add(password_node *hash_table[], char *find) {
  password_node *password_ptr;
  password_ptr = in_hash_table(hash_table, find);
  if (!password_ptr) {
    unsigned long password_code = ooat(find, strlen(find), NUM_BITS);
    password_ptr = malloc(sizeof(password_node));
    strcpy(password_ptr->password, find);
    password_ptr->total = 0;
    password_ptr->next = hash_table[password_code];
    hash_table[password_code] = password_ptr;
  }
  password_ptr->total++;
}

int already_added(
  char xs[][MAX_LEN + 1],
  int n,
  char *x
) {
  for (int i = 0; i < n; i++)
    if (strcmp(xs[i], x) == 0) return 1;
  return 0;
}

void insert_substrs(password_node *hash_table[], char *pswd) {
  int len = strlen(pswd), n_substrs = 0;
  char substr[MAX_LEN + 1];
  char all_substrs[MAX_SUBSTRS][MAX_LEN + 1];
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j <= len; j++) {
      strncpy(substr, pswd + i, j - i);
      substr[j - i] = '\0';
      if (!already_added(all_substrs, n_substrs, substr)) {
        add(hash_table, substr);
        strcpy(all_substrs[n_substrs], substr);
        n_substrs++;
      }
    }
  }
}

int main() {
  static password_node *hash_table[1 << NUM_BITS] = { NULL };
  password_node *password_ptr;
  int q, type;
  char pswd[MAX_LEN + 1];
  scanf("%d", &q);
  while (q--) {
    scanf("%d %s", &type, pswd);
    if (type == 1) {
      insert_substrs(hash_table, pswd);
    }
    if (type == 2) {
      password_ptr = in_hash_table(hash_table, pswd);
      printf("%d\n", password_ptr ? password_ptr->total : 0);
    }
  }
}
