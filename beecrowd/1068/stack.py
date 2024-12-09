def valid_expr(expr):
    pilha = []
    for c in expr:
        if c == '(':
            pilha.append(1)
        if c == ')':
            if len(pilha) == 0:
                return False
            pilha.pop()
    return len(pilha) == 0

def main():
    while True:
        try:
            expr = input()
        except EOFError:
            return
        if (valid_expr(expr)):
            print('correct')
        else:
            print('incorrect')

if __name__ == '__main__':
    main()
