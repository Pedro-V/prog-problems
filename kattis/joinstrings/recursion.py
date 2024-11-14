def print_rec(strs, indexes, i):
    print(strs[i], end='')
    for idx in indexes[i]:
        print_rec(strs, indexes, idx)

def main():
    n = int(input())
    # We need to initialize a and b here, since N-1 (number of operations) might
    # be 0.
    a, b = 1, 1
    strs = [""] * (n + 1)
    indexes = [[] for _ in range(n+1)]
    for i in range(1, n+1):
        strs[i] = input()
    for _ in range(n-1):
        a, b = map(int, input().split())
        indexes[a].append(b)
    print_rec(strs, indexes, a)
    print()

if __name__ == '__main__':
    main()

