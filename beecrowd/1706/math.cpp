#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vc = vector<char>;
using vb = vector<bool>;
using graph = vector<vi>;

int number_of_Bs(graph& g, vc& notes, vb& visited, int vertex) {
  int num = notes[vertex] == 'B';
  visited[vertex] = true;

  for (const auto x : g[vertex])
    if (!visited[x])
      num += number_of_Bs(g, notes, visited, x);
  return num;
}

int main() {
  int n, m, u, v, num_of_Bs, i;
  bool valid_towers;
  char sp;

  while (cin >> n >> m) {
    graph g(n);
    vb visited(n, false);
    vc notes(n);

    for (i = 0; i < n; i++)
      cin >> notes[i];
    
    for (i = 0; i < m; i++) {
      cin >> u >> v;
      g[u-1].push_back(v-1);
      g[v-1].push_back(u-1);
    }

    
    valid_towers = true;
    for (i = 0; i < n; i++) {
      if (visited[i])
        continue;
      num_of_Bs = number_of_Bs(g, notes, visited, i);
      if (num_of_Bs % 2 != 0) {
        valid_towers = false;
        break;
      }
    }
    cout << (valid_towers ? "Y\n" : "N\n");
  }
}
