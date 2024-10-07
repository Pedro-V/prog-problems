from operator import add, sub
from collections import defaultdict
from itertools import combinations

SF_LEN = 6

def identical(sf1, sf2, start, op):
    for i in range(SF_LEN):
        if sf1[i] != sf2[op(start, i) % SF_LEN]:
            return False
    return True

def are_identical(sf1, sf2):
    for start in range(SF_LEN):
        if identical(sf1, sf2, start, add) or identical(sf1, sf2, start, sub):
            return True
    return False

def solve(snowflake_table):
    for snowflakes in snowflake_table.values():
        for sf1, sf2 in combinations(snowflakes, 2):
            if are_identical(sf1, sf2):
                print('Twin snowflakes found.')
                return
    print('No two snowflakes are alike.')

def main():
    snowflake_table = defaultdict(list)
    n = int(input())
    for i in range(n):
        snow = [int(x) for x in input().split()]
        snowflake_table[sum(snow)].append(snow)
    solve(snowflake_table)
    
if __name__ == '__main__':
    main()
