# Essa é uma solução que gera todas as possibilidades de jogadas, usando
# combinatória.
# Como o tamanho da entrada é uma constante pequena, não tem risco de TLE
# fazendo ela.

from itertools import combinations, permutations

NUM_CARDS = 52
CARDS = range(1, NUM_CARDS + 1)

def generate_matchings(A, B):
    n = len(A)
    matchings = []

    for subset in combinations(B, n):
        for perm in permutations(subset):
            matching = tuple(zip(A, perm))
            leftover = set(B) - set(perm)
            matchings.append((matching, leftover))
    
    return matchings

def smallest_not_taken(arr, taken, threshold=0):
    """Returns smallest element in arr, that is not taken and greater than thresold."""
    for x in arr:
        if not taken[x] and x > threshold:
            return x
    return -1

def biggest_card_to_win(p1, p2, leftover):
    taken = [False] * (NUM_CARDS + 1)
    taken[0] = True
    for c in [*p1, *p2, leftover]:
        taken[c] = True
    num_wins = int(p1[0] > p1[1]) + int(p2[0] > p2[1])

    if num_wins == 0:
        return -1
    if num_wins == 2:
        return smallest_not_taken(CARDS, taken)
    return smallest_not_taken(CARDS, taken, leftover)


def best_next_card(A, B):
    best = -1
    for matchings, leftover in generate_matchings(A, B):
        card = biggest_card_to_win(*matchings, leftover.pop())
        if card == -1:
            return -1
        if card > best:
            best = card
    return best


def main():
    while True:
        a, b, c, x, y = map(int, input().split())
        if a == 0:
            return

        A = [x, y]
        B = [a, b, c]

        best = best_next_card(A, B)
        print(best)


if __name__ == '__main__':
    main()
