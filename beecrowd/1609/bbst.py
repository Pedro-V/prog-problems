def main():
    tc = int(input())
    for _ in range(tc):
        n = int(input())
        carneiros = map(int, input().split())
        unicos = set(carneiros)
        print(len(unicos))
            

if __name__ == '__main__':
    main()
