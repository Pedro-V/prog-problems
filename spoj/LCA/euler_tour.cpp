#include <bits/stdc++.h>
using namespace std;

// Solution to LCA using Euler Tour technique with Sparse Table for answering RMQs.

class SparseTable {
  vector<int> _arr;
  vector<vector<int>> st;

  int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
  }

public:
  SparseTable() {}

  SparseTable(vector<int>& arr) : _arr(arr) {
    int n = arr.size();
    int k = log2_floor(n);
    st.assign(k + 1, vector<int>(n));
    for (int j = 0; j < n; j++)
      st[0][j] = j;
    for (int i = 1; i <= k; i++)
      for (int j = 0; j + (1 << i) <= n; j++) {
        int left = st[i - 1][j];
        int right = st[i - 1][j + (1 << (i - 1))];
        st[i][j] = arr[left] < arr[right] ? left : right;
      }
  }

  int rmq(int L, int R) {
    int i = log2_floor(R - L + 1);
    int left = st[i][L];
    int right = st[i][R - (1 << i) + 1];
    return _arr[left] < _arr[right] ? left : right;
  }
};


class LCA {
  vector<int> height, euler, first;
  vector<bool> visited;
  SparseTable st;
  int n;

  void dfs(vector<vector<int>>& adj, int v, int p, int cur_height) {
    first[v] = euler.size();
    euler.push_back(v);
    height.push_back(cur_height);

    for (const auto u : adj[v])
      if (u != p) {
        dfs(adj, u, v, cur_height + 1);
        euler.push_back(v);
        height.push_back(cur_height);
      }
  }

public:
  LCA(vector<vector<int>>& adj, int root = 0) {
    n = adj.size();
    first.resize(n);
    euler.reserve(n * 2);
    visited.assign(n, false);
    dfs(adj, root, root, 0);
    st = SparseTable(height);
  }

  int lca(int u, int v) {
    int left = first[u], right = first[v];
    if (left > right)
      swap(left, right);
    return euler[st.rmq(left, right)];
  }
};


int main() {
  int tc, i, n, u, k, m, q, v;
  cin >> tc;
  for (i = 1; i <= tc; i++) {
    cin >> n;
    vector<vector<int>> adj(n);

    for (u = 0; u < n; u++) {
      cin >> m;
      for (k = 0; k < m; k++) {
        cin >> v;
        adj[u].push_back(v - 1);
      }
    }
    auto sol = LCA(adj);

    cin >> q;
    cout << "Case " << i << ":\n";
    while (q--) {
      cin >> u >> v;
      cout << sol.lca(u - 1, v - 1) + 1 << '\n';
    }
  }
}
