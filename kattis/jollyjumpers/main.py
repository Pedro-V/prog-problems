def check_is_jolly(n, nums):
    diffs = [False] * n

    for i in range(1, n):
        diff = abs(nums[i-1] - nums[i])
        # Pigeonhole principle for last condition.
        if (diff == 0 or diff > n-1 or diffs[diff] == True):
            return False
        diffs[diff] = True
    return True

def main():
    try:
        while True:
            n, *nums = map(int, input().split())
            is_jolly = check_is_jolly(n, nums)
            print('Jolly' if is_jolly else 'Not jolly')
    except EOFError:
        return

if __name__ == '__main__':
    main()
