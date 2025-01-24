#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;

void solve(vs& names, int k, int n) {
  int i, pos, j;

  for (i = 0; i < n && k > 0; i++) {
    pos = i;
    for (j = i + 1; j < n && j <= i + k; j++)
      if (names[j] < names[pos])
        pos = j;

    for (j = pos; j > i; j--) {
      swap(names[j], names[j - 1]);
      k--;
    }
  }
}

int main() {
  int tc = 0, i, n, k;
  while (true) {
    cin >> n >> k;
    if (n == 0 && k == 0)
      break;

    vs names(n);
    for (i = 0; i < n; i++)
      cin >> names[i];
    solve(names, k, n);

    cout << "Instancia " << ++tc << '\n';
    for (const auto& name : names)
      cout << name << ' ';
    cout << "\n\n";
  }
}
