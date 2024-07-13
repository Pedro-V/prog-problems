#include <stdio.h>
#include <math.h>

#define MAX_A 1000
#define MAX_B 200
#define MAX_K 200
#define MOD 1000000007

// This is a memoization backwards solution with 3 dimensions. It's O(M^2*N*K).
// The formulation of this solution is from Section 4.2 of Daniel Zingaro's
// Algorithm Thinking (https://nostarch.com/algorithmic-thinking-2nd-edition).

// Returns the maximum amount of ways we can build
// b[0..j] using exactly k substrings from a[0..i], with the restriction that a[i] == b[j].
int solve_ijk(char a[], char b[], int i, int j, int k, int memo[MAX_A][MAX_B][MAX_K + 1]) {
  if (memo[i][j][k] != -1)
    return memo[i][j][k];

  // Base case 1: we can form 'x' from '<something>x' using substring 'x'.
  if (j == 0 && k == 1 && a[i] == b[j])
    memo[i][j][k] = 1;
  // Base case 2: This covers a few situations actually.
  else if (i == 0 || j == 0 || k == 0)
    memo[i][j][k] = 0;
  // Base case 3: a[i] != b[j] breaks the subproblem definition.
  else if (a[i] != b[j])
    memo[i][j][k] = 0;
  else {
    int total = 0;
    // General case 1: We use a[i] as the final substring by itself.
    // Given a = "xxyzxy" and b = "xxy", we can solve it by using 'y' as the last substring.
    // But this can come from either matching b[2] with a[2] or a[5].
    // In the general case, this match can come from earlier as possible from a,
    // so we just try them all. This loop is the source of the algorithm's inefficiency.
    for (int q = 0; q < i; q++)
      total = (total + solve_ijk(a, b, q, j - 1, k - 1, memo)) % MOD;

    // General case 2: The last substring ends with a[i], but not by itself.
    // Since we know a[i] == b[j], we can solve for k with a[0..i-1] and
    // b[0..j-1] and extend this solution by tacking a[i] on the final substring.
    total = (total + solve_ijk(a, b, i - 1, j - 1, k, memo)) % MOD;
    memo[i][j][k] = total;
  }
 
  return memo[i][j][k];
}

// Any character of a might match the last character in b.
// Therefore, we try them all.
int solve(char a[], char b[], int a_len, int b_len, int num_substrings) {

  // This is big, so we avoid stack allocation and overflows by putting it on
  // static storage.
  static int memo[MAX_A][MAX_B][MAX_K + 1];

  for (int i = 0; i < a_len; i++)
    for (int j = 0; j < b_len; j++)
      for (int k = 0; k <= num_substrings; k++)
        memo[i][j][k] = -1;

  int result = 0;
  for (int i = 0; i < a_len; i++)
    result = (result + solve_ijk(a, b, i, b_len - 1, num_substrings, memo)) % MOD;
  return result;
}

int main() {
  int a_len, b_len, num_substrings;
  char a[MAX_A + 1], b[MAX_B + 1];

  scanf("%d%d%d", &a_len, &b_len, &num_substrings);
  scanf("%s", a);
  scanf("%s", b);
  printf("%d\n", solve(a, b, a_len, b_len, num_substrings));
}
