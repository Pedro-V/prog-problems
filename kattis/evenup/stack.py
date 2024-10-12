def main():
    n = int(input())
    nums = [int(c) for c in input().split()]
    stack = []
    for i in range(n):
        if not stack or (stack[-1] + nums[i]) % 2 != 0:
            stack.append(nums[i])
        else:
            stack.pop()
    print(len(stack))

if __name__ == '__main__':
    main()
