#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-8
#define min(a, b) (a) < (b) ? (a) : (b)
using dd = pair<double, double>;
using ddd = tuple<double, double, double>;

inline double second_derivative(double s, double x) {
  return 24*x - 4*s;
}

dd real_roots(double wc, double lc) {
  double r1, r2, r3, s = wc + lc;
  double delta = s*s - 4*wc*lc;
  r1 = 0;
  r2 = (s + sqrt(delta)) / 4;
  r3 = (s - sqrt(delta)) / 4;
  return {r1, min(r2, r3)};
}

ddd solve(double wc, double lc) {
  double s, delta, x1, x2, sec_dev_x1, sec_dev_x2, x_maximizes;
  auto [r1, r2] = real_roots(wc, lc);
  s = wc + lc;
  delta = s*s - 3*wc*lc;
  x1 = (s + sqrt(delta)) / 6;
  x2 = (s - sqrt(delta)) / 6;
  sec_dev_x1 = second_derivative(s, x1);
  sec_dev_x2 = second_derivative(s, x2);
  x_maximizes = sec_dev_x1 < 0 ? x1 : x2;
  return {x_maximizes, r1, r2 + EPS};
}

int main() {
  double wc, lc;
  while (cin >> wc >> lc) {
    auto [a, b, c] = solve(wc, lc);
    cout << fixed << setprecision(3) <<
      a << ' ' << b << ' ' << c << "\n";
  }
}
