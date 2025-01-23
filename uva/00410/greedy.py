def add_dummy_specimens(mass, s, c):
    for _ in range(s, 2*c):
        mass.append((0, -1))


def solve(mass):
    chambers = []
    n = len(mass)
    i = n - 1
    j = 0
    while j < i:
        a = mass[j]
        b = mass[i]
        # A chamber is a tuple of:
        # - its specimens masses
        # - the original index of the specimen with lesser mass.
        #   If no specimen are in the chamber, then this is n.
        if b[0] == 0:
            c = ((), n)
        elif a[0] == 0:
            c = ((b[0],), b[1])
        elif b[1] < a[1]:
            c = ((b[0], a[0]), b[1])
        else:
            c = ((a[0], b[0]), a[1])
        chambers.append(c)
        j += 1
        i -= 1
    return chambers

def calc_imbalance(mass, chambers):
    imbalance = 0
    avg = sum(map(lambda m: m[0], mass)) / len(chambers)
    for c in chambers:
        m = sum(c[0])
        imbalance += abs(m - avg)
    return imbalance

def main():
    tc = 0
    try:
        while True:
            tc += 1
            c, s = map(int, input().split())
            # We need to track the original index in the array.
            mass = [(int(x), i) for i, x in enumerate(input().split())]
            add_dummy_specimens(mass, s, c)
            mass.sort()
            chambers = solve(mass)
            imbalance = calc_imbalance(mass, chambers)
            chambers.sort(key=lambda c: c[1])

            print(f'Set #{tc}')
            for i, chamber in enumerate(chambers):
                print(f' {i}:', *chamber[0])
            print('IMBALANCE =', f'{imbalance:.5f}\n')
    except EOFError:
        return

if __name__ == '__main__':
    main()
