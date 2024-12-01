#!/usr/bin/env python3

def validLisp(tokens):
    pilha = []
    for token in tokens:
        if token == '(':
            pilha.append(token)
        elif token == ')':
            if not pilha:
                return False
            pilha.pop()
    return len(pilha) == 0

class Node:
    def __init__(self, children):
        self.children = children

    def __str__(self) -> str:
        output = ''
        output += str(self.children[0]) + '('
        output += ','.join(map(str, self.children[1:]))
        output += ')'
        return output

def parse(tokens, i=0):
    if tokens[i] != '(' and tokens[i] != ')':
        return (tokens[i], i + 1)

    children = []
    i += 1
    while i < len(tokens) and tokens[i] != ')':
        child, i = parse(tokens, i)
        children.append(child)
    n = Node(children)
    return (n, i + 1)

def main():
    tc = int(input())
    for i in range(tc):
        tokens = input().split()
        if not validLisp(tokens):
            print('Syntax error')
            continue
        root, _ = parse(tokens)
        print(root)

if __name__ == '__main__':
    main()

