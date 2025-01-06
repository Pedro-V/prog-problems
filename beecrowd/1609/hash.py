def main():
    n = int(input())
    for _ in range(n):
        xs = map(int, input().split())
        s = set(xs)
        print(len(s))

if __name__ == '__main__':
    main()
