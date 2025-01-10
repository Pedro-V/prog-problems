def main():
    n = int(input())
    for _ in range(n):
        words = input().split()
        words.sort(key=lambda x: len(x), reverse=True)
        print(*words)

if __name__ == '__main__':
    main()
