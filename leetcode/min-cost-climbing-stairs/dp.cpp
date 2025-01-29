#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

#define min(a, b) (a) < (b) ? (a) : (b)

// DP solution with O(n) time and O(1) space.
int solve(vi& cost) {
  int n, i, cur, next1, next2;

  n = cost.size();
  next1 = cost[n - 2];
  next2 = cost[n - 1];

  for (i = n - 3; i >= 0; i--) {
    cur = cost[i] + min(next1, next2);
    next2 = next1;
    next1 = cur;
  }

  return min(next1, next2);
}

int main() {
  vi cost = {10, 15, 20};
  cout << solve(cost) << '\n';
}
