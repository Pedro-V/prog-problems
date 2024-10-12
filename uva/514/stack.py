def can_marshal(rails, n):
    stack = []
    index = 0
    for i in range(1, n+1):
        stack.append(i)
        while stack and rails[index] == stack[-1]:
            index += 1
            stack.pop()
    return len(stack) == 0

def main():
    while True:
        n = int(input())
        if n == 0:
            break
        while True:
            rails = [int(c) for c in input().split()]
            if rails[0] == 0:
                break
            print('Yes' if can_marshal(rails, n) else 'No')
        print()

if __name__ == '__main__':
    main()

