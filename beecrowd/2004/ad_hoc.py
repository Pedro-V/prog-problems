from collections import defaultdict


def main():
    tc = int(input())
    for _ in range(tc):
        n = int(input())

        foods = defaultdict(list)
        for _ in range(n):
            t, grams = map(int, input().split())
            foods[t].append(grams)

        total = 0
        for grams in foods.values():
            well_sized = [g for g in grams if 10 <= g <= 100]
            if len(well_sized) == 0:
                total += max(grams)
            else:
                total += max(well_sized)
        print(total)


if __name__ == "__main__":
    main()
