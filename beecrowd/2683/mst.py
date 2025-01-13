# TODO: This Python solution is receiving TLE for some unknown reason.
# I'm 99% sure it shouldn't receive TLE.

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

def kruskal(edges, num_nodes, max_cost=False):
    sets = list(range(num_nodes))
    size = [1] * num_nodes
    cost = 0

    edges.sort(key=lambda x: x[2], reverse=max_cost)
    for u, v, weight in edges:
        if find(sets, u) == find(sets, v):
            continue
        cost += weight
        union(sets, size, u, v)

    return cost

def main():
    n = int(input())
    num_nodes = 1000 + 1
    edges = []

    for _ in range(n):
        e = tuple(map(int, input().split()))
        edges.append(e)
    
    print(kruskal(edges, num_nodes, max_cost=True))
    print(kruskal(edges, num_nodes, max_cost=False))


if __name__ == '__main__':
    main()
