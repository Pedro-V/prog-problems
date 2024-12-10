#include <bits/stdc++.h>
using namespace std;

#define max(a, b) (a > b ? a : b)

struct Node {
  Node *left, *right;

  bool is_leaf() const {
    return !left && !right;
  }
};

class DefaultDict {
  unordered_map<string, Node*> data;

public:
  Node* operator[](const string& key) {
    if (!data.contains(key))
      data[key] = new Node();
    return data[key];
  }

  ~DefaultDict() {
    for (auto& pair : data)
      delete pair.second;
  }
};

int solve(Node *n) {
  int left, right;

  if (n->is_leaf())
    return 0;

  left = solve(n->left);
  right = solve(n->right);

  if (left == 0 && right == 0)
    return 1;
  if (left != right)
    return max(left, right);
  return left + 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string a, b, result, plus, arrow;
  int i, num_reactions, min_containers;
  DefaultDict table;

  cin >> num_reactions;
  while (num_reactions != 0) {
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
