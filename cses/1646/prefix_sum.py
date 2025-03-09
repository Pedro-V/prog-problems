def main():
    n, q = map(int, input().split())
    vals = [int(x) for x in input().split()]

    prefix_sum = [0] * (n+1)
    for i in range(1, n+1):
        prefix_sum[i] = vals[i-1] + prefix_sum[i - 1]

    for _ in range(q):
        a, b = map(int, input().split())
        print(prefix_sum[b] - prefix_sum[a-1])

if __name__ == '__main__':
    main()
