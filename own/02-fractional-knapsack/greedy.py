def solve(items, cap):
    items.sort(key=lambda t: t[1] / t[0], reverse=True)
    max_val, i = 0, 0
    while cap > 0:
        w, v = items[i]
        ratio = v / w
        units = min(cap, w)
        max_val += ratio * units
        cap -= units
        i += 1
    return max_val

def main():
    tc = int(input())
    for _ in range(tc):
        n, cap = map(int, input().split())
        items = []
        for _ in range(n):
            w, v = map(int, input().split())
            items.append((w, v))
        max_val = solve(items, cap)
        print(f'{max_val:.2f}')

if __name__ == '__main__':
    main()
