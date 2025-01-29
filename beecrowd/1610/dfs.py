# Slight modification of Tarjan's topological sort, based on DFS.

def visit(g, has_permanent_mark, has_temporary_mark, u):
    if has_temporary_mark[u]:
        return True

    has_temporary_mark[u] = True
    for v in g[u]:
        if has_permanent_mark[v]:
            continue
        has_cycle = visit(g, has_permanent_mark, has_temporary_mark, v)
        if has_cycle:
            return True
    has_permanent_mark[u] = True
    return False

def solve(g, n):
    has_permanent_mark = [False] * n
    has_temporary_mark = [False] * n
    for u in range(n):
        if not has_permanent_mark[u]:
            has_cycle = visit(g, has_permanent_mark, has_temporary_mark, u)
            if has_cycle:
                return True
    return False

def main():
    tc = int(input())
    for _ in range(tc):
        n, m = map(int, input().split())
        g = [set() for _ in range(n)]

        for _ in range(m):
            u, v = map(int, input().split())
            g[u-1].add(v-1)
        has_cycle = solve(g, n)
        print('SIM' if has_cycle else 'NAO')

if __name__ == '__main__':
    main()
