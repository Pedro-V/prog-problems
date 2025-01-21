ADD_OP = 1
BATTLE_OP = 2
RAFAEL_SET = 1

def find(sets, s):
    rep = s
    while sets[rep] != rep:
        rep = sets[rep]
    while sets[s] != rep:
        sets[s], s = rep, sets[s]
    return rep

def union(sets, s1, s2, sizes, points):
    r1 = find(sets, s1)
    r2 = find(sets, s2)
    if sizes[r2] > sizes[r1]:
        r1, r2 = r2, r1
    sets[r2] = r1
    sizes[r1] += sizes[r2]
    points[r1] += points[r2]
    return r1

def battle(sets, s1, s2, points):
    r1 = find(sets, s1)
    r2 = find(sets, s2)
    winner = r1 if points[r1] > points[r2] else r2
    return int(winner == find(sets, RAFAEL_SET))

def main():
    while True:
        n, m = map(int, input().split())
        if n == m == 0:
            return

        points = [0] + [int(x) for x in input().split()]
        sets = [i for i in range(n+1)]
        sizes = [1] * (n + 1)
        rafael_wins = 0

        for _ in range(m):
            op, a, b = map(int, input().split())
            if op == ADD_OP:
                union(sets, a, b, sizes, points)
            elif op == BATTLE_OP:
                rafael_wins += battle(sets, a, b, points)
        print(rafael_wins)

if __name__ == '__main__':
    main()
