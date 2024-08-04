#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

#define max(a, b) (a > b ? a : b)

typedef struct {
  int left, right;
  int max_sum, max_element;
} segtree_node;

typedef struct {
  int max_sum, max_element;
} node_info;

node_info get_info(segtree_node n) {
  return (node_info){ n.max_sum, n.max_element };
}

node_info maximize_info(node_info a, node_info b) {
  int max_sum, max_element, combined_sum;

  combined_sum = a.max_element + b.max_element;
  max_element = max(a.max_element, b.max_element);
  max_sum = max(a.max_sum, max(b.max_sum, combined_sum));
  return (node_info){max_sum, max_element};
}

void init_segtree(segtree_node segtree[], int node, int left, int right) {
  int mid;

  segtree[node].left = left;
  segtree[node].right = right;

  if (left == right)
    return;

  mid = (left + right) / 2;
  init_segtree(segtree, node * 2, left, mid);
  init_segtree(segtree, node * 2 + 1, mid + 1, right);
}

node_info fill_segtree(segtree_node segtree[], int node, int seq[]) {
  node_info left_info, right_info, ret_info;

  if (segtree[node].left == segtree[node].right) {
    segtree[node].max_sum = -1;
    segtree[node].max_element = seq[segtree[node].left];
    return get_info(segtree[node]);
  }

  left_info = fill_segtree(segtree, node * 2, seq);
  right_info = fill_segtree(segtree, node * 2 + 1, seq);
  ret_info = maximize_info(left_info, right_info);

  segtree[node].max_element = ret_info.max_element;
  segtree[node].max_sum = ret_info.max_sum;

  return get_info(segtree[node]);
}

node_info query_segtree(segtree_node segtree[], int node, int left, int right) {
  node_info left_info, right_info;

  if (segtree[node].left > right || segtree[node].right < left)
    return (node_info){ -1, -1 };

  if (left <= segtree[node].left && segtree[node].right <= right)
    return get_info(segtree[node]);

  left_info = query_segtree(segtree, node * 2, left, right);
  right_info = query_segtree(segtree, node * 2 + 1, left, right);

  if (left_info.max_element == -1)
    return right_info;
  if (right_info.max_element == -1)
    return left_info;
  return maximize_info(left_info, right_info);
}

node_info update_segtree(segtree_node segtree[], int node, int index, int new_value) {
  node_info left_info, right_info, ret_info;

  // Case 0: We reached the leaf for the index.
  if (segtree[node].left == segtree[node].right && segtree[node].left == index) {
    segtree[node].max_element = new_value;
    return get_info(segtree[node]);
  }
  
  // Case 1: index is on our left.
  if (index <= segtree[node * 2].right) {
    left_info = update_segtree(segtree, node * 2, index, new_value);
    right_info = get_info(segtree[node * 2 + 1]);
  } // Case 2: index is on our right.
  else {
    left_info = get_info(segtree[node * 2]);
    right_info = update_segtree(segtree, node * 2 + 1, index, new_value);
  }

  ret_info = maximize_info(left_info, right_info);
  segtree[node].max_element = ret_info.max_element;
  segtree[node].max_sum = ret_info.max_sum;

  return get_info(segtree[node]);
}

int main() {
  static int seq[SIZE + 1] = {0, 10, 8, 6, 15};
  static segtree_node segtree[4*SIZE + 1];
  int i, seq_len, num_ops, x, y;
  char op;

  scanf("%d", &seq_len);
  for (i = 1; i <= seq_len; i++)
    scanf("%d", &seq[i]);
  init_segtree(segtree, 1, 1, seq_len);
  fill_segtree(segtree, 1, seq);

  scanf("%d", &num_ops);
  for (i = 0; i < num_ops; i++) {
    scanf(" %c %d %d", &op, &x, &y);
    if (op == 'Q')
      printf("%d\n", query_segtree(segtree, 1, x, y).max_sum);
    else // Note that seq isn't updated. Just because of shorter code.
      update_segtree(segtree, 1, x, y);
  }
}
