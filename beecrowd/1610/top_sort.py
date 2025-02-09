# Slight modification of Kahn's topological sort.
def has_cycle(incoming, outgoing):
    n = len(incoming)
    nodes_no_incoming_edge = [i for i in range(n) if not incoming[i]]

    while nodes_no_incoming_edge:
        u = nodes_no_incoming_edge.pop()
        for v in outgoing[u]:
            incoming[v].remove(u)
            if not incoming[v]:
                nodes_no_incoming_edge.append(v)
        outgoing[u].clear()

    return not all(not s for s in incoming)

def main():
    tc = int(input())
    for _ in range(tc):
        n, m = map(int, input().split())
        incoming = [set() for _ in range(n)]
        outgoing = [set() for _ in range(n)]
        for _ in range(m):
            u, v = map(int, input().split())
            outgoing[u-1].add(v-1)
            incoming[v-1].add(u-1)
        if has_cycle(incoming, outgoing):
            print('SIM')
        else:
            print('NAO')

if __name__ == '__main__':
    main()
