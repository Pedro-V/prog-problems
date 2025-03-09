#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using AL = vector<vi>;

void reachable_from(AL& g, int n, int x, int y) {
  int k, i, j;
  int idx = n * x + y;
  // vertical

  for (i = 0; i < n; i++)
    if (!(i < (x-1) || i > (x+1)))
      g[idx].push_back(n*i+j);
  // horizontal
  for (j = 0; j < n; j++)
    if (!(j < (y-1) || j > (y+1)))
      g[idx].push_back(n*i+j);
  // 1st diagonal (top-left to bottom-right)
  k = min(x, y);
  for (i = x - k, j = y - k; i < n && j < n; i++, j++)
    if (!(((i < x-1) && (j < y-1)) || ((i > x+1) && (j > y+1))))
      g[idx].push_back(n*i+j);
  // 2nd diagonal (top-right to bottom-left)
  k = min(x, n-1-y);
  if (k < 0) k = 0;
  for (i = x - k, j = y + k; i < n && j >= 0; i++, j--)
    if (!(((i < x-1) && (j > y+1)) || ((i > x+1) && (j < y-1))))
      g[idx].push_back(n*i+j);
}

AL build_graph(size_t n) {
  AL g(n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      reachable_from(g, n, i, j);
  return g;
}

size_t num_valid_patterns(const AL& g, int u, ll k) {
  if (k == 0)
    return g[u].size();
  size_t res = 0;
  for (const auto v : g[u])
    res += num_valid_patterns(g, v, k-1);
  return res;
}

int main() {
  size_t n, k;
  while (cin >> n >> k) {
    const auto g = build_graph(n);
    size_t res = k;
    if (k > 0)
      for (int v = 0; v < g.size(); v++)
        res += num_valid_patterns(g, v, k);
    cout << res << '\n';
  }
}
