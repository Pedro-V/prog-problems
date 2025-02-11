#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int find(vi& sets, int s) {
  int tmp, rep = s;
  while (sets[rep] != rep)
    rep = sets[rep];
  while (sets[s] != rep) {
    tmp = sets[s];
    sets[s] = rep;
    s = tmp;
  }
  return rep;
}

int union_sets(vi& sets, vi& sizes, int s1, int s2) {
  int r1 = find(sets, s1), r2 = find(sets, s2);
  if (sizes[r2] > sizes[r1])
    swap(r1, r2);
  sizes[r1] += sizes[r2];
  sets[r2] = r1;
  return r1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, q, x, y, i;
  // We shouldn't print a '\n' after the last case, otherwise
  // we get presentation error.
  bool prev_test = false;

  while (cin >> n >> m >> q) {
    if (prev_test)
      cout << '\n';

    vi sets(n + 1), sizes(n + 1, 1);

    for (i = 1; i <= n; i++) 
      sets[i] = i;

    for (i = 0; i < m; i++) {
      cin >> x >> y;
      union_sets(sets, sizes, x, y);
    }

    for (i = 0; i < q; i++) {
      cin >> x >> y;
      if (find(sets, x) == find(sets, y))
        cout << "S\n";
      else
        cout << "N\n";
    }
    prev_test = true;
  }
}
