#include <bits/stdc++.h>
using namespace std;
using point = pair<int, int>;
using vp = vector<point>;
using iid = tuple<int, int, double>;
using viid = vector<iid>;

double dist(point p, point q) {
  auto x1 = p.first, y1 = p.second;
  auto x2 = q.first, y2 = q.second;
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
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

double kruskal(vector<iid>& edges, int num_nodes) {
  vector<int> sets(num_nodes), size(num_nodes, 1);
  double cost = 0;

  for (int i = 0; i < num_nodes; i++)
    sets[i] = i;

  sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
    return get<2>(a) < get<2>(b);
  });
  for (const auto& [u, v, w] : edges) {
    if (find(sets, u) == find(sets, v))
      continue;
    union_sets(sets, size, u, v);
    cost += w;
  }
  return cost;
}

void build_full_graph(viid& edges, vp& coords) {
  int i, j, n = coords.size();
  for (i = 0; i < n; i++)
    for (j = i + 1; j < n; j++) {
      iid edge = {i, j, dist(coords[i], coords[j])};
      edges.push_back(edge);
    }
}

int main() {
  int i, tc, n;
  double min_dist;
  cin >> tc;
  while (tc--) {
    cin >> n;
    vp coords(n);
    for (i = 0; i < n; i++)
      cin >> coords[i].first >> coords[i].second;
    viid edges;
    build_full_graph(edges, coords);
    min_dist = kruskal(edges, n) / 100;
    printf("%.2lf\n", min_dist);
  }
}
