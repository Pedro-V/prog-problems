from math import dist

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

def build_full_graph(coords):
    n = len(coords)
    edges = []
    for i in range(n):
        for j in range(i + 1, n):
            edge = (i, j, dist(coords[i], coords[j]))
            edges.append(edge)
    return edges

def main():
    tc = int(input())
    for _ in range(tc):
        n = int(input())
        coords = []
        for _ in range(n):
            coord = tuple(map(int, input().split()))
            coords.append(coord)
        edges = build_full_graph(coords)
        min_dist = kruskal(edges, n) / 100
        print(f'{min_dist:.2f}')

if __name__ == '__main__':
    main()

