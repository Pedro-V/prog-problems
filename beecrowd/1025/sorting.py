from bisect import bisect_left

def bin_search(xs, x):
    i = bisect_left(xs, x)
    if i != len(xs) and xs[i] == x:
        return i
    return -1

def main():
    tc = 0
    while True:
        n, q = map(int, input().split())
        if n == 0 and q == 0:
            return

        tc += 1
        print(f'CASE# {tc}:')

        marbles = []
        for _ in range(n):
            marble = int(input())
            marbles.append(marble)
        marbles.sort()
        
        for _ in range(q):
            x = int(input())
            idx = bin_search(marbles, x)
            if idx == -1:
                print(f'{x} not found')
            else:
                print(f'{x} found at {idx + 1}')

if __name__ == '__main__':
    main()
