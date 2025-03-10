def main():
    n = int(input())
    strs = [None] * (n + 1)
    for i in range(1, n+1):
        strs[i] = input()
    for _ in range(n-1):
        a, b = map(int, input().split())
        strs[a] += strs[b]
    print(strs[a])

if __name__ == '__main__':
    main()
