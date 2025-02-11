#include <bits/stdc++.h>
using namespace std;

// Solution to LCA with Binary Lifting.
class LCA {
  int L;
  int timer;
  vector<int> tin, tout;
  vector<vector<int>> up, adj;

  void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;

    for (int i = 1; i <= L; i++)
      up[v][i] = up[up[v][i-1]][i-1];

    for (const auto u : adj[v])
      if (u != p)
        dfs(u, v);

    tout[v] = ++timer;
  }

  // If v was visited after u, and left before u, then u is an ancestor of v.
  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }

public:
  LCA(int n, vector<vector<int>>& adj_list) : adj(adj_list) {
    L = ceil(log2(n));
    timer = 0;
    tin.resize(n);
    tout.resize(n);
    up.assign(n, vector<int>(L + 1));
    dfs(0, 0);
  }

  int lca(int u, int v) {
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;
    for (int i = L; i >= 0; i--)
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    return up[u][0];
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
    auto sol = LCA(n, adj);

    cin >> q;
    cout << "Case " << i << ":\n";
    while (q--) {
      cin >> u >> v;
      cout << sol.lca(u - 1, v - 1) + 1 << '\n';
    }
  }
}
