def main():
    tc = 0
    while True:
        a = input()
        if a == '0':
            return
        seq = input()
        tc += 1
        if tc != 1:
            print()
        print(f'Instancia {tc}')
        print('verdadeira' if a in seq else 'falsa')

if __name__ == '__main__':
    main()
