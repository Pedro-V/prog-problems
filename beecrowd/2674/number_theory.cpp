#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

const int SIZE = 1e5;
bool is_prime[SIZE];
const size_t pot10[] = {
  1, 10, 100, 1'000, 10'000
};

vi digits(int n) {
  int i, num_digits = floor(log10(n)) + 1;
  vector<int> digits;
  digits.reserve(num_digits);

  for (i = 1; i <= num_digits; i++)
    digits.push_back((n % pot10[i]) / pot10[i-1]);
  return digits;
}

void sieve(size_t n) {
  size_t i, j, p;
  vi nums(n+1);

  for (i = 0; i <= n; i++)
    nums[i] = i;

  for (p = 2; p <= floor(sqrt(n)); p++) {
    if (nums[p] == 0)
      continue;
    for (j = p * p; j <= n; j += p)
      nums[j] = 0;
  }

  for (const auto n : nums)
    is_prime[n] = n != 0;
  is_prime[0] = is_prime[1] = false;
}

const string classification(int n) {
  if (!is_prime[n])
    return "Nada";
  for (const auto d : digits(n))
    if (!is_prime[d])
      return "Primo";
  return "Super";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  sieve(SIZE - 1);

  while (cin >> n)
    cout << classification(n) << '\n';
}
