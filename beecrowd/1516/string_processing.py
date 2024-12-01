def main():
    while True:
        n, m = map(int, input().split())
        if n == 0:
            break

        lines = []
        for _ in range(n):
            lines.append(input())

        a, b = map(int, input().split())
        horizontal_times = b // m
        vertical_times = a // n

        for line in lines:
            output = ''.join(map(lambda c: c * horizontal_times, line))
            output = [output] * vertical_times
            print(*output, sep='\n')

        print()

if __name__ == '__main__':
    main()
