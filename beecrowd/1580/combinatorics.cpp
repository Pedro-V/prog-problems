#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 1e3;

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

  // Fast Modular Exponentiation.
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

  // Fermat's Little Theorem.
  size_t flt(size_t b, size_t M) {
    if (b % M == 0)
      return 0;
    return mod_pow(b, M-2, M);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  Factorial<MAX_N> fact(MOD);
  string word;
  while (cin >> word) {
    unordered_map<char, int> freq;
    for (char c : word)
      freq[c]++;

    size_t num_anagrams = fact.get(word.length());
    for (auto [_, count] : freq)
      num_anagrams = (num_anagrams * fact.get_inv(count)) % MOD;

    cout << num_anagrams << '\n';
  }
  return 0;
}

