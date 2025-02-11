#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using iii = tuple<int, int, int>;
using edge_list = vector<iii>;

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

pair<ll, ll> kruskal(edge_list& el, int n) {
  vi sets(n + 1), sizes(n + 1, 1);
  ll num_components = n, min_cost = 0;

  for (int i = 1; i <= n; i++)
    sets[i] = i;

  sort(el.begin(), el.end(), [](const auto& a, const auto& b) {
    return get<2>(a) < get<2>(b);
  });

  for (const auto [u, v, c] : el) {
    if (find(sets, u) == find(sets, v))
      continue;
    union_sets(sets, sizes, u, v);
    min_cost += c;
    num_components--;
  }

  return {num_components, min_cost};
}

int main() {
  int n, k, u, cost;
  edge_list el;
  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> k;
    for (int j = 0; j < k; j++) {
      cin >> u >> cost;
      el.push_back({i, u, cost});
    }
  }
  const auto [num_components, min_cost] = kruskal(el, n);
  cout << num_components << ' ' << min_cost << '\n';
}
