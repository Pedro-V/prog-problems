// This is the assignment problem (aka Bipartite Matching with Capacity).
// We solve it using the max flow reduction.
#include <bits/stdc++.h>
using namespace std;
using vb = vector<bool>;
using vi = vector<int>;
using matrix = vector<vi>;

bool bfs(matrix& capacity, vi& parent, int source, int sink) {
  int v, u, n = capacity.size();
  vb visited(n, false);
  queue<int> q;

  q.push(source);
  visited[source] = true;

  while (!q.empty()) {
    u = q.front();
    q.pop();

    for (v = 0; v < n; v++) {
      if (visited[v] || capacity[u][v] <= 0)
        continue;

      parent[v] = u;
      if (v == sink)
        return true;

      q.push(v);
      visited[v] = true;
    }
  }

  return false;
}

int edmonds_karp(matrix& capacity, int source = 0, int sink = 0) {
  int path_flow, v, max_flow = 0, n = capacity.size();
  sink = sink ? sink : n - 1;
  vi parent(n, -1);

  while (bfs(capacity, parent, source, sink)) {
    path_flow = numeric_limits<int>::max();
    for (v = sink; v != source; v = parent[v])
      path_flow = min(path_flow, capacity[parent[v]][v]);
    max_flow += path_flow;
    
    for (v = sink; v != source; v = parent[v]) {
      capacity[parent[v]][v] -= path_flow;
      capacity[v][parent[v]] += path_flow;
    }
  }

  return max_flow;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int tc, i, k1, k2, n, m, r, size;
  string shirt1, shirt2;
  const unordered_map<string, int> table = {
    {"XXL", 1},
    {"XL", 2},
    {"L", 3},
    {"M", 4},
    {"S", 5},
    {"XS", 6},
  };
  cin >> tc;
  while (tc--) {
    cin >> n >> m;

    r = n / 6;
    // 1 source, 6 shirt types, m volunteers, 1 sink.
    size = 1 + 6 + m + 1;
    matrix capacity(size, vi(size));

    for (i = 1; i <= 6; i++)
      capacity[0][i] = r;
    for (i = 0; i < m; i++) {
      cin >> shirt1 >> shirt2;
      k1 = table.at(shirt1);
      k2 = table.at(shirt2);
      capacity[k1][1 + 6 + i] = 1;
      capacity[k2][1 + 6 + i] = 1;
    }
    for (i = 1 + 6; i < 1 + 6 + m; i++)
      capacity[i][size-1] = 1;

    if (m == edmonds_karp(capacity))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}
