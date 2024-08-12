#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
 * Randomized (Monte Carlo) solution.
 * It picks a random piece in the slab, then checks (via binary search) if that
 * piece satisfies the threshold (1/3 for one friend, 2/3 for both).
 *
 * This idea is due to Daniel Zingaro's Algorithmic Thinking (2024).
 */

#define SIZE 200000
#define NUM_ATTEMPTS 60

int random_piece(int left, int width) {
  return (rand() % width) + left;
}

int lowest_index(int pieces[], int num_pieces, int at_least) {
  int low, high, mid;
  low = 0;
  high = num_pieces;
  while (high - low >= 1) {
    mid = (low + high) / 2;
    if (pieces[mid] < at_least)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}

int num_in_range(int pieces[], int num_pieces, int left, int right) {
  int left_index = lowest_index(pieces, num_pieces, left);
  int right_index = lowest_index(pieces, num_pieces, right + 1);
  return right_index - left_index;
}

void solve(int yokan[], int *pieces_for_flavor[], int num_of_flavor[], int left, int right) {
  int attempt, rand_piece, flavor, result;
  int width = right - left + 1;
  double threshold = width / 3.0;
  int first_flavor = 0;

  for (attempt = 0; attempt < NUM_ATTEMPTS; attempt++) {
    rand_piece = random_piece(left, width);
    flavor = yokan[rand_piece];
    result = num_in_range(pieces_for_flavor[flavor], num_of_flavor[flavor], left, right);

    if (result >= 2 * threshold) {
      printf("YES\n");
      return;
    }

    if (result >= threshold) 
      first_flavor = flavor;
  }

  if (first_flavor == 0) {
    printf("NO\n");
    return;
  }

  for (attempt = 0; attempt < NUM_ATTEMPTS; attempt++) {
    rand_piece = random_piece(left, width);
    flavor = yokan[rand_piece];
    if (flavor == first_flavor)
      continue;
    result = num_in_range(pieces_for_flavor[flavor], num_of_flavor[flavor], left, right);

    if (result >= threshold) {
      printf("YES\n");
      return;
    }
  }

  printf("NO\n");
}

void init_flavor_arrays(int yokan[], int num_pieces, int *pieces_for_flavor[]) {
  static int cur_of_flavor[SIZE + 1];
  int i, flavor, j;
  for (i = 1; i <= num_pieces; i++) {
    flavor = yokan[i];
    j = cur_of_flavor[flavor];
    pieces_for_flavor[flavor][j] = i;
    cur_of_flavor[flavor]++;
  }
}

int main() {
  static int yokan[SIZE + 1], num_of_flavor[SIZE + 1], *pieces_for_flavor[SIZE + 1];
  int num_pieces, num_flavors, i, num_queries, l, r;
  // Seed the PRNG with the current time.
  srand((unsigned) time(NULL));
  scanf("%d%d", &num_pieces, &num_flavors);

  for (i = 1; i <= num_pieces; i++) {
    scanf("%d", &yokan[i]);
    num_of_flavor[yokan[i]]++;
  }

  for (i = 1; i <= num_flavors; i++)
    pieces_for_flavor[i] = malloc(num_of_flavor[i] * sizeof(int));

  init_flavor_arrays(yokan, num_pieces, pieces_for_flavor);

  scanf("%d", &num_queries);
  for (i = 0; i < num_queries; i++) {
    scanf("%d%d", &l, &r);
    solve(yokan, pieces_for_flavor, num_of_flavor, l, r);
  }
}
