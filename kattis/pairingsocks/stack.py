def main():
    n = int(input())
    sock_stack = []
    aux_stack = []
    moves = 0

    for s in input().split():
        sock_stack.append(int(s))

    while sock_stack:
        if not aux_stack or aux_stack[-1] != sock_stack[-1]:
            aux_stack.append(sock_stack.pop())
        else:
            sock_stack.pop()
            aux_stack.pop()
        moves += 1

    if aux_stack:
        print('impossible')
    else:
        print(moves)

if __name__ == '__main__':
    main()
