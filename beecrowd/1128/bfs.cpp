// Kusaraju finds all SCCs.
// The algorithm for checking strong connectivity can be simpler: we just need to
// perform BFS on G and the transpose of G. If in both the BFS traverses all
// vertices, then it's strongly connected.
#include <bits/stdc++.h>
using namespace std;
using vb = vector<bool>;
using vi = vector<int>;
using AL = vector<vi>;

bool bfs(const AL& g, int start = 0) {
  queue<int> q;
  int n = g.size();
  vb visited(n, false);
  int u, num_visited = 0;

  visited[start] = true;
  num_visited++;
  q.push(start);

  while (!q.empty()) {
    u = q.front();
    q.pop();

    for (const auto v : g[u])
      if (!visited[v]) {
        visited[v] = true;
        num_visited++;
        q.push(v);
      }
  }

  return num_visited == n;
}

int is_strongly_connected(const AL& g) {
  int n = g.size();
  if (!bfs(g))
    return 0;

  AL transposed_g(n);
  for (int u = 0; u < n; u++)
    for (const auto v : g[u])
      transposed_g[v].push_back(u);

  return bfs(transposed_g);
}

int main() {
  int i, n, m, u, v, t;
  while (cin >> n >> m) {
    if (n == 0)
      break;
    AL g(n);
    for (i = 0; i < m; i++) {
      cin >> u >> v >> t;
      g[u-1].push_back(v-1);
      if (t == 2)
        g[v-1].push_back(u-1);
    }
    cout << is_strongly_connected(g) << '\n';
  }
}
