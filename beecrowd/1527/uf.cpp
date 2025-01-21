#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

const int ADD_OP = 1, BATTLE_OP = 2, RAFAEL_SET = 1;

int find(vi& sets, int s) {
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

int union_sets(vi& sets, vi& sizes, vi& points, int s1, int s2) {
  int r1 = find(sets, s1), r2 = find(sets, s2);
  if (sizes[r2] > sizes[r1])
    swap(r1, r2);
  sets[r2] = r1;
  sizes[r1] += sizes[r2];
  points[r1] += points[r2];
  return r1;
}


int battle(vi& sets, vi& points, int s1, int s2) {
  int r1 = find(sets, s1), r2 = find(sets, s2);
  if (points[r1] == points[r2]) return 0;
  int winner = points[r1] > points[r2] ? r1 : r2;
  return winner == find(sets, RAFAEL_SET);
}

int main() {
  int n, m, rafael_wins, op, a, b, i;
  while (true) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;

    vi sets(n+1), points(n+1), sizes(n+1, 1);
    rafael_wins = 0;
    for (i = 1; i <= n; i++) {
      cin >> points[i];
      sets[i] = i;
    }

    for (i = 0; i < m; i++) {
      cin >> op >> a >> b;
      if (op == ADD_OP)
        union_sets(sets, sizes, points, a, b);
      else if (op == BATTLE_OP)
        rafael_wins += battle(sets, points, a, b);
    }
    cout << rafael_wins << '\n';
  }
}
