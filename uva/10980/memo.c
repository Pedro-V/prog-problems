#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
 * Due to the input spec limiting the apple amount of a scheme to 100 and the
 * initial asked apple amount to 100, we know that we can't buy more than 199, because
 * if somehow the optimal solution involved buying 200 (or more) apples, that should
 * include an optimal subsolution to buying 100 apples (using the maximum scheme amount),
 * which means that subsolution is already the cheapest for buying at least 100
 * apples, which is the maximum we can be asked.
 * Therefore, we set SIZE to 199 + 1, for use in solve().
 */

#define SIZE 200
double memo[SIZE]; /* make memo global because function calls are getting lengthy. */

#define MAX_SCHEMES 20
#define min(a, b) (a < b ? a : b)

/* Returns the optimal price for buying exactly k apples. */
double solve_k(
  int scheme_amounts[],
  double scheme_prices[],
  int num_schemes,
  double unit_price,
  int k
) {
  if (memo[k] != -1)
    return memo[k];

  if (k == 0) return 0;

  double p, subproblem_price, curr_price, min_price;
  int n, i;

  /* Case where we buy a single apple as the last purchase. */
  subproblem_price = solve_k(scheme_amounts, scheme_prices, num_schemes, unit_price, k - 1);
  min_price = subproblem_price + unit_price;

  /* Case where we use a scheme for the last purchase. */
  for (i = 0; i < num_schemes; i++) {
    n = scheme_amounts[i];
    p = scheme_prices[i];

    if (k >= n) {
      subproblem_price = solve_k(scheme_amounts, scheme_prices, num_schemes, unit_price, k - n);
      curr_price = subproblem_price + p;
      min_price = min(min_price, curr_price);
    }
  }

  memo[k] = min_price;
  return memo[k];
}

double solve(
  int scheme_amounts[],
  double scheme_prices[],
  int num_schemes,
  double unit_price,
  int num_apples
) {
  double curr_price, min_price = INT_MAX;
  int i;

  for (i = num_apples; i < SIZE; i++) {
    curr_price = solve_k(scheme_amounts, scheme_prices, num_schemes, unit_price, i);
    min_price = min(min_price, curr_price);
  }
  return min_price;
}

int get_number(int *n) {
  int ch = getchar(), ret = 0;
  while (ch != ' ' && ch != '\n') {
    ret = ret * 10 + ch - '0';
    ch = getchar();
  }
  *n = ret;
  return ch == ' ';
}

int main() {
  int more, num_schemes, num_apples, i,
      scheme_amounts[MAX_SCHEMES], test_case = 0;
  double unit_price, result, scheme_prices[MAX_SCHEMES];

  while (scanf("%lf%d ", &unit_price, &num_schemes) != EOF) {
    test_case++;

    for (i = 0; i < SIZE; i++)
      memo[i] = -1;

    for (i = 0; i < num_schemes; i++)
      scanf("%d%lf ", &scheme_amounts[i], &scheme_prices[i]);
    printf("Case %d:\n", test_case);

    more = get_number(&num_apples);
    while (more) {
      result = solve(scheme_amounts, scheme_prices, num_schemes, unit_price, num_apples);
      printf("Buy %d for $%.2f\n", num_apples, result);
      more = get_number(&num_apples);
    }

    /* For the last number in the last line of a test case. */
    result = solve(scheme_amounts, scheme_prices, num_schemes, unit_price, num_apples);
    printf("Buy %d for $%.2f\n", num_apples, result);
  }
}
