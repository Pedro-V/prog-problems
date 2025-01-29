#include <bits/stdc++.h>
using namespace std;

#define SIZE 5
#define valid_idx(i) (i >= 0 && i < SIZE)

using ii = pair<int, int>;
using vii = vector<ii>;

template <typename T>
using matrix = vector<vector<T>>;

vii neighborhood(int i, int j) {
  vii initial_positions = {{i, j+1}, {i, j-1}, {i-1, j}, {i+1, j}};
  vii valid_positions;

  for (const auto [x, y] : initial_positions)
    if (valid_idx(x) && valid_idx(y)) 
      valid_positions.emplace_back(x, y);

  return valid_positions;
}

void dfs(matrix<int>& mat, matrix<bool>& visited, int i, int j) {
  visited[i][j] = true;
  for (const auto [x, y] : neighborhood(i, j))
    if (mat[x][y] == 0 && !visited[x][y])
      dfs(mat, visited, x, y);
}

int main() {
  int tc, x, i, j;
  cin >> tc;
  while (tc--) {
    matrix<int> mat;
    matrix<bool> visited;

    for (i = 0; i < SIZE; i++) {
      vector<int> v1(SIZE);
      vector<bool> v2(SIZE);
      mat.push_back(v1);
      visited.push_back(v2);

      for (j = 0; j < SIZE; j++)
        cin >> mat[i][j];
      }

    dfs(mat, visited, 0, 0);
    cout << (visited[SIZE-1][SIZE-1] ? "COPS\n" : "ROBBERS\n");
  }
  return 0;
}
