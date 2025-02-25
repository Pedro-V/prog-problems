#include <bits/stdc++.h>
using namespace std;

// gcd of all numbers in xs.
int gcd_all(vector<int> xs) {
  int res = xs[0];
  for (size_t i = 1; i < xs.size(); i++)
    res = gcd(res, xs[i]);
  return res;
}

int main() {
  int a, b, c, m;
  while (cin >> a >> b >> c) {
    m = max({a, b, c});
    if (m*m != a*a + b*b + c*c - m*m)
      cout << "tripla\n";
    else if (gcd_all({a, b, c}) != 1)
      cout << "tripla pitagorica\n";
    else
      cout << "tripla pitagorica primitiva\n";
  }
}
