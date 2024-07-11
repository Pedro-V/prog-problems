#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// This is a dynamic programming solution with two dimensions:
// i (first i games considered for Team 1)
// j (first j games considered for Team 2)
// Both start at 1, with 0 reserved for zero games.

#define MAX_GAMES 1000
#define max(a, b) (a > b ? a : b)

int dp[MAX_GAMES][MAX_GAMES];

int solve_dp(char outcome1[], char outcome2[], int goals1[], int goals2[], int n) {
  int first, second, third, fourth;

  dp[0][0] = 0;
  dp[0][1] = 0;
  dp[1][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int team1_won = outcome1[i] == 'W' && outcome2[j] == 'L' && goals1[i] > goals2[j];
      int team2_won = outcome1[i] == 'L' && outcome2[j] == 'W' && goals1[i] < goals2[j];

      if (team1_won || team2_won)
        first = dp[i - 1][j - 1] + goals1[i] + goals2[j];
      else
        first = 0;

      second = dp[i - 1][j - 1];
      third = dp[i - 1][j];
      fourth = dp[i][j - 1];

      dp[i][j] = max(first, max(second, max(third, fourth)));
    }
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++)
      printf("%d ", dp[i][j]);
    printf("\n");
  }

  return dp[n][n];
}

int main() {
  int n, goals1[MAX_GAMES + 1], goals2[MAX_GAMES + 1];
  char outcome1[MAX_GAMES + 1], outcome2[MAX_GAMES + 1];
  outcome1[0] = ' ';
  outcome2[0] = ' ';

  // Ending with a space is important so that the last \n doesn't stays in
  // stdin for us to read it into outcome arrays.
  scanf("%d ", &n);
  for (int i = 1; i <= n; i++)
    scanf("%c", &outcome1[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d ", &goals1[i]);
  for (int i = 1; i <= n; i++)
    scanf("%c", &outcome2[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d ", &goals2[i]);

  printf("%d\n", solve_dp(outcome1, outcome2, goals1, goals2, n));
}
