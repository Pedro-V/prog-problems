from math import dist

def main():
    try:
        while True:
            r1, x1, y1, r2, x2, y2 = map(int, input().split())
            p = (x1, y1)
            q = (x2, y2)
            if dist(p, q) + r2 <= r1:
                print('RICO')
            else:
                print('MORTO')
    except EOFError:
        return

if __name__ == '__main__':
    main()
