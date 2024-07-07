#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 256
#define max(a, b) (a) > (b) ? (a) : (b)

typedef struct node {
  int candy;
  struct node *left, *right;
} node;

node *new_house(int candy) {
  node *house = malloc(sizeof(node));
  house->candy = candy;
  house->left = NULL;
  house->right = NULL;
  return house;
}

node *new_nonhouse(node *left, node *right) {
  node *nonhouse = malloc(sizeof(node));
  nonhouse->left = left;
  nonhouse->right = right;
  return nonhouse;
}

int tree_candy(node *tree) {
  if (!tree->left && !tree->right)
    return tree->candy;
  return tree_candy(tree->left) + tree_candy(tree->right);
}

/*
 * This implements a recursively-defined walk on the tree that comes back to the
 * root and has no extra unnecessary steps, and returns the number of steps in it.
 * Call this walk specification 'Default'.
 *
 * There may be many walks that fulfills Default, but all have the
 * same number of steps.
 *
 * This is the key to the solution of the problem:
 * The optimal walk is a subset of another walk that fulfills Default.
 *
 * Because the optimal walk always end on the deepest node, then all we need to
 * do is eliminate the steps that go back to the root in Default, and we have
 * the length of the optimal walk.
 *
 * Going from the deepest node to the root equals the tree's height.
 */
int tree_streets(node *tree) {
  if (!tree->left && !tree->right)
    return 0;
  return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

int tree_height(node *tree) {
  if (!tree->left && !tree->right)
    return 0;
  int max_height = max(tree_height(tree->left), tree_height(tree->right));
  return max_height + 1;
}

void tree_solve(node *tree) {
  int candy = tree_candy(tree);
  int height = tree_height(tree);
  int num_streets = tree_streets(tree) - height;
  printf("%d %d\n", num_streets, candy);
}

node *read_tree_helper(char *line, int *pos) {
  node *tree;
  tree = malloc(sizeof(node));

  if (line[*pos] == '(') {
    (*pos)++;
    tree->left = read_tree_helper(line, pos);
    (*pos)++;
    tree->right = read_tree_helper(line, pos);
    (*pos)++;
  }
  else { // must be a number.
    int characters_read;
    sscanf(line + (*pos), "%d%n", &tree->candy, &characters_read);
    (*pos) += characters_read;
  }

  return tree;
}

node *read_tree(char *line) {
  int n = 0;
  return read_tree_helper(line, &n);
}

int main() {
  char input[MAX_LEN + 1];
  for (int i = 0; i < 5; i++) {
    fgets(input, MAX_LEN + 1, stdin);
    node *tree = read_tree(input);
    tree_solve(tree);
  }
}
