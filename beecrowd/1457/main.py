def main():
    tc = int(input())
    for _ in range(tc):
        line = input().strip()
        idx = line.find('!')
        k = len(line) - idx
        n = int(line[:idx])
        res = 1
        while n >= 1:
            res *= n
            n -= k
        print(res)

if __name__ == '__main__':
    main()
