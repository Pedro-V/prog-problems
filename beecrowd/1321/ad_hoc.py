NUM_CARDS = 52


def find_highest_not_shown(cards, shown, minimum=0):
    highest = 0
    idx = -1
    for i, card in enumerate(cards):
        if card > minimum and card > highest and not shown[i]:
            highest = card
            idx = i
    return idx


def find_lowest_not_shown(cards, shown):
    lowest = NUM_CARDS + 1
    idx = -1
    for i, card in enumerate(cards):
        if card < lowest and not shown[i]:
            lowest = card
            idx = i
    return idx


def make_worst_play(king_cards, king_shown, princess_cards, princess_shown):
    """Makes worst play and returns wether the king lost."""
    i = find_highest_not_shown(king_cards, king_shown)
    j = find_highest_not_shown(princess_cards, princess_shown, king_cards[i])
    if j == -1:
        j = find_lowest_not_shown(princess_cards, princess_shown)
    princess_shown[j] = True
    king_shown[i] = True

    return princess_cards[j] > king_cards[i]


def solve(a, b, c, x, y):
    card_taken = [False] * (NUM_CARDS + 1)
    for idx in [a, b, c, x, y]:
        card_taken[idx] = True

    princess_cards = [a, b, c]
    princess_shown = [False, False, False]
    king_cards = [x, y]
    king_shown = [False, False]

    lost_amount = 0
    lost_amount += make_worst_play(king_cards, king_shown, princess_cards, princess_shown)
    lost_amount += make_worst_play(king_cards, king_shown, princess_cards, princess_shown)

    if lost_amount == 2:
        return -1

    j = find_highest_not_shown(princess_cards, princess_shown)
    card_left = princess_cards[j]
    ans = -1
    for k in range(card_left + 1, NUM_CARDS + 1):
        if not card_taken[k]:
            ans = k
            break
    return ans


def main():
    while True:
        a, b, c, x, y = map(int, input().split())
        if a == 0:
            break
        res = solve(a, b, c, x, y)
        print(res)


if __name__ == "__main__":
    main()
