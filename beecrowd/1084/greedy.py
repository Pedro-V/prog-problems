def solve(digits, d):
    stack = []

    for digit in digits:
        while stack and d > 0 and stack[-1] < digit:
            stack.pop()
            d -= 1
        stack.append(digit)

    while d > 0:
        stack.pop()
        d -= 1

    return stack


def main():
    while True:
        n, d = map(int, input().split())
        if n == d == 0:
            break
        digits = input()
        prize = solve(digits, d)
        print(*prize, sep='')

if __name__ == '__main__':
    main()
