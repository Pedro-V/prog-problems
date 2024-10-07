from collections import Counter
import operator
from itertools import starmap, combinations, repeat

# From itertools recipes: https://docs.python.org/3/library/itertools.html#itertools-recipes
def subslices(seq):
    # subslices('ABCD') -> A AB ABC ABCD B BC BCD C CD D
    slices = starmap(slice, combinations(range(len(seq) + 1), 2))
    return map(operator.getitem, repeat(seq), slices)

def main():
    n = int(input())
    table = Counter()
    for _ in range(n):
        op, s = input().split()
        if op == '1':
            table.update(set(subslices(s)))
        else:
            print(table[s])

if __name__ == '__main__':
    main()
