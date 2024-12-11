#include <bits/stdc++.h>
using namespace std;

#define max(a, b) (a > b ? a : b)
#define NOT_DEFINED (-1)

struct Node {
  Node *left, *right;
  int num_containers = NOT_DEFINED;

  bool is_leaf() const {
    return !left && !right;
  }
};


template <class K, class V>
class DefaultDict {
  unordered_map<K, V*> data;

public:
  V* operator[](const K& key) {
    if (!data.contains(key))
      data[key] = new V();
    return data[key];
  }

  ~DefaultDict() {
    for (auto& pair : data)
      delete pair.second;
  }
};


int solve(Node *n) {
  int left, right;

  if (n->num_containers != NOT_DEFINED) 
    return n->num_containers;

  if (n->is_leaf()) {
    n->num_containers = 0;
    return 0;
  }

  left = solve(n->left);
  right = solve(n->right);

  if (left == 0 && right == 0)
    n->num_containers = 1;
  else if (left != right) 
    n->num_containers = max(left, right);
  else
    n->num_containers = left + 1;
  return n->num_containers;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string a, b, result, plus, arrow;
  int i, num_reactions, min_containers;

  cin >> num_reactions;
  while (num_reactions != 0) {
    DefaultDict<string, Node> table;

    for (i = 0; i < num_reactions; i++) {
      cin >> a >> plus >> b >> arrow >> result;
      table[result]->left = table[a];
      table[result]->right = table[b];
    }

    min_containers = solve(table[result]);
    cout << result << " requires " << min_containers << " containers\n";
    cin >> num_reactions;
  }
}
