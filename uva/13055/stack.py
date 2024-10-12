def main():
    num_queries = int(input())
    stack = []
    for _ in range(num_queries):
        query, *args = input().split()

        if query == 'Sleep':
            stack.append(args[0])
        elif query == 'Kick' and stack:
            stack.pop()
        elif query == 'Test':
            print(stack[-1] if stack else 'Not in a dream')

if __name__ == '__main__':
    main()
