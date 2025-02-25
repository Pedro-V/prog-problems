from math import gcd

def main():
    while True:
        try:
            a, b, c = map(int, input().split())
        except EOFError:
            break
        m = max(a, b, c)
        if not m*m == a*a + b*b + c*c - m*m:
            print('tripla')
        elif gcd(a, b, c) != 1:
            print('tripla pitagorica')
        else:
            print('tripla pitagorica primitiva')

if __name__ == '__main__':
    main()
