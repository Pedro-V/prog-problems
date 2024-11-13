def main():
    num_tests = int(input())
    for i in range(1, num_tests+1):
        vals = [int(n) for n in input().split()]
        vals.sort()
        print(f'Case {i}: {vals[1]}')

if __name__ == '__main__':
    main()
