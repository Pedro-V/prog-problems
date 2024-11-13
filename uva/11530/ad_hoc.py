def main():
    keys = [
        '', 'abc', 'def',
        'ghi', 'jkl', 'mno',
        'pqrs', 'tuv', 'wxyz',
        '', ' ', '',
    ]

    num_tests = int(input())
    for i in range(1, num_tests+1):
        text = input()
        num_pressings = 0
        for c in text:
            for key_set in keys:
                if c in key_set:
                    num_pressings += key_set.index(c) + 1
        print(f'Case #{i}: {num_pressings}')

if __name__ == '__main__':
    main()
