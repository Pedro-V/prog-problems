#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const int SIZE = 9;

vi digits(const string& s) {
  vector<int> digits(SIZE);
  int j = s.length() - 1;
  for (int i = SIZE-1; j >= 0; i--)
    digits[i] = s[j--] - '0';
  return digits;
}

// Assumes n is the number with less digits.
int solve(const vi& n_digits, const vi& m_digits) {
  int carry = 0;
  int carry_count = 0;

  for (int i = SIZE-1; i >= 0; i--)
    carry_count += (carry = m_digits[i] >= (10 - (n_digits[i] + carry)));
  return carry_count;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  string n, m;
  while (cin >> n >> m) {
    if (n == "0" && m == "0")
      break;
    if (n.length() > m.length())
      swap(n, m);
    const vi n_digits = digits(n);
    const vi m_digits = digits(m);
    const int ans = solve(n_digits, m_digits);
    if (ans == 0)
      cout << "No carry operation.\n";
    else if (ans == 1)
      cout << "1 carry operation.\n";
    else
      cout << ans << " carry operations.\n";
  }
}
