def solve(words):
    words.sort()
    n = len(words)
    for i in range(1, n):
        if words[i].startswith(words[i-1]):
            return "Conjunto Ruim"
    return "Conjunto Bom"
    
def main():
    n = int(input())
    while n:
        words = []
        for _ in range(n):
            words.append(input())
        print(solve(words))
        n = int(input())

if __name__ == '__main__':
    main()
