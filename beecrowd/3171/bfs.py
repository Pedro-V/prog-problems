def bfs(adj_list):
    n = len(adj_list)
    visited = [False for _ in range(n + 1)]
    next_nodes = []
    current_nodes = [1]
    while current_nodes:
        for i in current_nodes:
            if not visited[i]:
                visited[i] = True
                next_nodes += adj_list[i]
        current_nodes = next_nodes
        next_nodes = []
    return sum(visited)

def main():
    num_lights, num_conns = map(int, input().split())
    adj_list = {i: [] for i in range(1, num_lights + 1)}
    for _ in range(num_conns):
        i, j = map(int, input().split())
        adj_list[i].append(j)
        adj_list[j].append(i)
    num_visited = bfs(adj_list)
    if num_visited == num_lights:
        print('COMPLETO')
    else:
        print('INCOMPLETO')
        
if __name__ == '__main__':
    main()
