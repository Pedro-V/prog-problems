#include <bits/stdc++.h>
using namespace std;

using iii = tuple<int, int, int>;

void sort_tuples(vector<iii>& xs, bool reverse) {
  sort(xs.begin(), xs.end(), [reverse](const auto& a, const auto& b) {
      return reverse ? (get<2>(a) > get<2>(b))
      : (get<2>(a) < get<2>(b));
      });
}

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

int kruskal(vector<iii>& edges, int num_nodes, bool max_cost = false) {
  vector<int> sets(num_nodes + 1), size(num_nodes + 1, 1);
  int cost = 0;

  for (int i = 1; i <= num_nodes; i++)
    sets[i] = i;

  sort_tuples(edges, max_cost);
  for (const auto& [u, v, w] : edges) {
    if (find(sets, u) == find(sets, v))
      continue;
    union_sets(sets, size, u, v);
    cost += w;
  }
  return cost;
}

int main() {
  int n, u, v, w, num_nodes = 1000 + 1;
  cin >> n;
  vector<iii> edges(n);

  for (int i = 0; i < n; i++) {
    cin >> u >> v >> w;
    iii t(u, v, w);
    edges[i] = t;
  }

  cout << kruskal(edges, num_nodes, true) << '\n';
  cout << kruskal(edges, num_nodes, false) << '\n';
}
