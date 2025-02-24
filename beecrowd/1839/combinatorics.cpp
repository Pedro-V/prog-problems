#include <bits/stdc++.h>
using namespace std;

const int SIZE = 50;
const int MOD  = 1e9 + 7;

int count_blacks(char grid[SIZE+1][SIZE+1], int x1, int y1, int x2, int y2) {
  int i, j, res = 0;
  for (i = x1; i <= x2; i++)
    for (j = y1; j <= y2; j++)
      res += grid[i][j] == '#';
  return res;
}

template <size_t N>
class Factorial {
public:
  Factorial(const size_t mod) {
    fact[0] = fact[1] = 1;
    inv_fact[0] = inv_fact[1] = 1;
    for (size_t i = 2; i <= N; i++) {
      fact[i] = i * fact[i-1] % mod;
      inv_fact[i] = flt(i, mod) * inv_fact[i-1] % mod;
    }
  }

  size_t get(size_t n) {
    return fact[n];
  }
  size_t get_inv(size_t n) {
    return inv_fact[n];
  }

private:
  array<size_t, N + 1> fact;
  array<size_t, N + 1> inv_fact;

  size_t mod_pow(size_t base, size_t exp, size_t mod) {
    size_t res = 1;
    base = base % mod;
    while (exp > 0) {
      if (exp % 2 == 1)
        res = (res * base) % mod;
      base = (base * base) % mod;
      exp /= 2;
    }
    return res;
  }

  size_t flt(size_t b, size_t M) {
    if (b % M == 0)
      return 0;
    return mod_pow(b, M-2, M);
  }
};
Factorial<SIZE*SIZE> fact(MOD);

size_t num_permutations_with_repetition(size_t n, const vector<int>& freqs) {
  size_t res = fact.get(n);
  for (const auto freq : freqs)
    res = res * fact.get_inv(freq) % MOD;
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  static char grid[SIZE+1][SIZE+1];
  int n, m, i, j, num_whites, num_blacks, total, res;
  int x1, x2, y1, y2;

  cin >> n >> m;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++)
      cin >> grid[i][j];

  while (cin >> x1 >> y1 >> x2 >> y2) {
    num_blacks = count_blacks(grid, x1, y1, x2, y2);
    num_whites = (x2 - x1 + 1) * (y2 - y1 + 1) - num_blacks;
    total = num_whites + num_blacks;
    res = num_permutations_with_repetition(total, {num_whites, num_blacks}) - 1;
    cout << res << '\n';
  }
}
