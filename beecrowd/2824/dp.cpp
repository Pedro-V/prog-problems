#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using matrix = vector<vi>;

int lcs(const string& s1, const string& s2) {
  int i, j, n = s1.length(), m = s2.length();
  matrix dp(n + 1, vi(m + 1, 0));

  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++)
      if (s1[i - 1] == s2[j - 1])
        dp[i][j] = dp[i-1][j-1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

  return dp[n][m];
}


int main() {
  string s1, s2;
  cin >> s1 >> s2;
  cout << lcs(s1, s2) << '\n';
}
