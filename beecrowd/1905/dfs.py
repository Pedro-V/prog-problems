SIZE = 5

def neighborhood(i, j):
    pos = [(i, j+1), (i, j-1), (i-1, j), (i+1, j)]
    return [
        p for p in pos if
        (p[0] >= 0 and p[0] < SIZE) and 
        (p[1] >= 0 and p[1] < SIZE)
    ]

def dfs(mat, i, j, visited):
    visited[i][j] = True
    for x, y in neighborhood(i, j):
        if mat[x][y] == 0 and not visited[x][y]:
            dfs(mat, x, y, visited)

def main():
    tc = int(input())
    for i in range(tc):
        mat = []
        visited = [[False] * SIZE for _ in range(SIZE)]

        # We do the below check because Beecrowd's input is not consistent.
        # Sometimes we have blank lines before matrix, sometimes not.
        n = SIZE
        t = input().split()
        if t:
            n -= 1
            mat.append(list(map(int, t)))

        for _ in range(n):
            line = [int(x) for x in input().split()]
            mat.append(line)
        dfs(mat, 0, 0, visited)
        print('COPS' if visited[SIZE-1][SIZE-1] else 'ROBBERS')


if __name__ == '__main__':
    main()
