def try_build_initial_grid(n, pole):
    initial_grid = [0] * n
    for i in range(n):
        car_num, change = pole[i]
        initial_pos = i + change
        if initial_pos < 0 or initial_pos >= n or initial_grid[initial_pos] != 0:
            return []
        initial_grid[initial_pos] = car_num
    return initial_grid

def main():
    while True:
        n = int(input())
        if n == 0:
            break

        pole = []
        for _ in range(n):
            car_num, change = map(int, input().split())
            pole.append((car_num, change))
        
        initial_grid = try_build_initial_grid(n, pole)
        if initial_grid:
            print(*initial_grid)
        else:
            print(-1)

if __name__ == '__main__':
    main()
