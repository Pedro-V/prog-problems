#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Same as dp.c, but takes advantage of the fact that in the DP solution we
// only access the current and the previous row (because of the access patterns
// i, j, i - 1, j - 1).
//
// We just substitute every dp[i - 1]for previous and dp[i] for current.

#define MAX_GAMES 1000
#define max(a, b) (a > b ? a : b)

int solve_dp(char outcome1[], char outcome2[], int goals1[], int goals2[], int n) {
  int first, second, third, fourth;

  int previous[MAX_GAMES + 1], current[MAX_GAMES + 1];

  previous[0] = 0;
  previous[1] = 0;
  current[0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int team1_won = outcome1[i] == 'W' && outcome2[j] == 'L' && goals1[i] > goals2[j];
      int team2_won = outcome1[i] == 'L' && outcome2[j] == 'W' && goals1[i] < goals2[j];

      if (team1_won || team2_won)
        first = previous[j - 1] + goals1[i] + goals2[j];
      else
        first = 0;

      second = previous[j - 1];
      third = previous[j];
      fourth = current[j - 1];

      current[j] = max(first, max(second, max(third, fourth)));
    }
    for (int k = 0; k <= n; k++)
      previous[k] = current[k];
  }

  return current[n];
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

