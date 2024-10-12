def main():
    while True:
        num_soldiers, num_reports = map(int, input().split())
        if num_soldiers == 0:
            break
        soldiers = [None] * (num_soldiers + 1)

        for i in range(1, num_soldiers+1):
            left_buddy = -1 if i-1 < 1 else i-1
            right_buddy = -1 if i+1 > num_soldiers else i+1
            soldiers[i] = [left_buddy, right_buddy]

        for _ in range(num_reports):
            left, right = map(int, input().split())
            living_left = soldiers[left][0]
            living_right = soldiers[right][1]

            if living_left == -1:
                print('*', end=' ')
            else:
                print(living_left, end=' ')
                soldiers[living_left][1] = living_right

            if living_right == -1:
                print('*')
            else:
                print(living_right)
                soldiers[living_right][0] = living_left
        print('-')

if __name__ == '__main__':
    main()
