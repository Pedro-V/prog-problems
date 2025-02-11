#include <bits/stdc++.h>
using namespace std;

class TreeAncestor {
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

public:
  TreeAncestor(int n, vector<int>& parent) {
    L = ceil(log2(n));
    timer = 0;
    tin.reserve(n);
    tin.reserve(n);
    up.assign(n, vector<int>(L + 1));
    adj.assign(n, vector<int>());

    for (int i = 1; i < n; i++) {
      adj[i].push_back(parent[i]);
      adj[parent[i]].push_back(i);
    }

    dfs(0, 0);
  }

  int getKthAncestor(int node, int k) {
  }
}
