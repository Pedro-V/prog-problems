# Union-Find solution.

def find(sets, i):
    rep = i
    while sets[rep] != rep:
        rep = sets[rep]
    while sets[i] != i:
        sets[i], i = rep, sets[i]
    return rep
    
def union(sets, size, i, j):
    rep1 = find(sets, i)
    rep2 = find(sets, j)
    if size[rep1] > size[rep2]:
        sets[rep2]  = rep1
        return rep1
    else:
        sets[rep1] = rep2
        return rep2

def main():
    num_ligths, num_conns = map(int, input().split())
    sets = [i for i in range(num_ligths + 1)]
    size = [0 for _ in range(num_ligths + 1)]
    for _ in range(num_conns):
        i, j = map(int, input().split())
        union(sets, size, i, j)
    first_rep = find(sets, 1)
    if all(map(lambda x: find(sets, x) == first_rep, range(2, num_ligths+1))):
        print('COMPLETO')
    else:
        print('INCOMPLETO')
        
if __name__ == '__main__':
    main()
