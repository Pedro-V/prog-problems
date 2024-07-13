#include <stdio.h>
#include <math.h>

#define MAX_A 1000
#define MAX_B 200
#define MAX_K 200
#define MOD 1000000007

// This is a memoization backwards solution similar to `memo_slow.c`.
// But we change the subproblem description so that it returns the number of
// ways we can build b[0...j] using exactly k substrings from a[0..i].
// This drops the requirement of a[i] == b[j], which allows for replacing the
// loop in the general case 1 for a simple lookup.
// The memo array now contains structs with two info:
// - how many solutions with the old a[i] == b[j] restriction (end_at_i).
//   (This is still needed, as seen bellow)
// - the total amount of solutions, without this restriction (total).
//   Note that total >= end_at_i, for any element in the memo array.
// It's an O(M*N*K) solution
// The formulation of this solution is from Section 4.2 of Daniel Zingaro's
// Algorithm Thinking (https://nostarch.com/algorithmic-thinking-2nd-edition).

typedef struct {
  int end_at_i;
  int total;
} pair;

pair solve(char a[], char b[], int i, int j, int k, pair memo[MAX_A][MAX_B][MAX_K + 1]) {
  if (memo[i][j][k].total != -1)
    return memo[i][j][k];

  int end_at_i, total;

  // Base case, where we look at b's 1st char and a[i] may or may not be equal to b[j].
  if (j == 0 && k == 1) {
    // If it does, then end_at_i is 1, otherwise 0.
    end_at_i = a[i] == b[j] ? 1 : 0;
    if (i == 0)
      total = end_at_i;
    // If i != 0, there may be earlier characters in a[0..i-1] that are equal to b[j],
    // which are then valid solutions to this base case, and must be added to total.
    else
      total = end_at_i + solve(a, b, i - 1, j, k, memo).total;
    memo[i][j][k] = (pair){ end_at_i, total };
    return memo[i][j][k];
  }

  if (i == 0 || j == 0 || k == 0) {
    memo[i][j][k] = (pair){ 0, 0 };
    return memo[i][j][k];
  }

  // The general cases are the same as in `memo.c`, but
  // here we eliminate the previous loop by a simple lookup.
  if (a[i] != b[j])
    end_at_i = 0;
  else {
    end_at_i = (solve(a, b, i - 1, j - 1, k - 1, memo).total + // General case 1.
                solve(a, b, i - 1, j - 1, k, memo).end_at_i);  // General case 2.
    end_at_i = end_at_i % MOD;
  }

  // The total for this is just the total for a[0..i-1] + the amount of
  // solutions that end at a[i].
  total = (end_at_i + solve(a, b, i - 1, j, k, memo).total) % MOD;
  memo[i][j][k] = (pair){ end_at_i, total };

  return memo[i][j][k];
}

int main() {
  int a_len, b_len, num_substrings;
  char a[MAX_A + 1], b[MAX_B + 1];
  static pair memo[MAX_A][MAX_B][MAX_K + 1];

  scanf("%d%d%d", &a_len, &b_len, &num_substrings);
  scanf("%s", a);
  scanf("%s", b);

  for (int i = 0; i < a_len; i++)
    for (int j = 0; j < b_len; j++)
      for (int k = 0; k <= num_substrings; k++)
        memo[i][j][k] = (pair){ -1, -1 };

  int result = solve(a, b, a_len - 1, b_len - 1, num_substrings, memo).total;
  printf("%d\n", result);
}
