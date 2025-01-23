#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using iii = tuple<int, int, int>;
using viii = vector<iii>;
#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

int find(vector<int>& sets, int s) {
  int tmp, rep = s;
  while (sets[rep] != rep)
    rep = sets[rep];
  while (sets[s] != s) {
    tmp = sets[s];
    sets[s] = rep;
    s = tmp;
  }
  return rep;
}

int union_sets(vector<int>& sets, vector<int>& sizes, int s1, int s2) {
  int r1 = find(sets, s1), r2 = find(sets, s2);
  if (sizes[r2] > sizes[r1])
    swap(r1, r2);
  sizes[r1] += sizes[r2];
  sets[r2] = r1;
  return r1;
}

vii kruskal(vector<iii>& edges, int num_nodes) {
  vii tree_edges(num_nodes - 1);
  ii edge;
  int i;
  vector<int> sets(num_nodes + 1), size(num_nodes + 1, 1);

  for (i = 0; i < num_nodes; i++)
    sets[i] = i;
  sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
    return get<2>(a) < get<2>(b);
  });

  i = 0;
  for (const auto& [u, v, w] : edges) {
    if (find(sets, u) == find(sets, v))
      continue;
    union_sets(sets, size, u, v);
    edge.first = min(u, v);
    edge.second = max(u, v);
    tree_edges[i++] = edge;
  }

  return tree_edges;
}

int main() {
  int i, n, m, x, y, w, tc = 1;
  while (true) {
    cin >> n >> m;
    if (n == 0) break;

    viii edges(m);
    for (i = 0; i < m; i++) {
      cin >> x >> y >> w;
      iii t = {x, y, w};
      edges[i] = t;
    }

    auto tree_edges = kruskal(edges, n);
    cout << "Teste " << tc++ << '\n';
    for (const auto& [u, v] : tree_edges)
      cout << u << ' ' << v << '\n';
    cout << '\n';
  }
}

