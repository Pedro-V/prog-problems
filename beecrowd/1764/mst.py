def find(sets, s):
    rep = s
    while sets[rep] != rep:
        rep = sets[rep]
    while sets[s] != s:
        s, sets[s] = sets[s], rep
    return rep

def union(sets, size, s1, s2):
    r1 = find(sets, s1)
    r2 = find(sets, s2)
    if size[r2] > size[r1]:
        r1, r2 = r2, r1
    size[r1] += 1
    sets[r2] = sets[r1]
    return r1

def kruskal(edges, m, n):
    sets = list(range(m))
    size = [1] * m
    cost = 0

    edges.sort(key=lambda x: x[2])
    for u, v, weight in edges:
        if find(sets, u) == find(sets, v):
            continue
        cost += weight
        union(sets, size, u, v)

    return cost

def main():
    while True:
        m, n = map(int, input().split())
        if m == n == 0:
            return
        edges = []
        for _ in range(n):
            e = tuple(map(int, input().split()))
            edges.append(e)
        print(kruskal(edges, m, n))

if __name__ == '__main__':
    main()
