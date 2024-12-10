# Since n can go up to 10⁶, the brute force algorithm which has a complexity of 
# 2n + nlogn => 2*(10^6 + 10^7) => 20M, which for multiple test cases gives TLE.

# The bottleneck is any step that costs O(n*log n), in our case, sorting.
# Idea: We can avoid O(n*log n) sorting by using a hash table and counting sort
# because we know the avg consumption is always between [0, 200].

from collections import defaultdict

def counting_sort(table, high):
    present = [False] * (high + 1)
    sorted_arr = []

    for x in table:
        present[x] = True
    for i in range(high + 1):
        if present[i]:
            elem = table[i], i
            sorted_arr.append(elem)
    return sorted_arr

def main():
    case_num = 0
    while True:
        n = int(input())
        if n == 0:
            return
        case_num += 1
        if case_num != 1:
            print()

        table = defaultdict(int)
        total_consump = 0
        total_people = 0
        for _ in range(n):
            people, consump = map(int, input().split())
            avg_consump = consump // people
            table[avg_consump] += people
            total_consump += consump
            total_people += people
        sorted_arr = counting_sort(table, 200)
        avg = total_consump / total_people

        output = ' '.join([f'{people}-{consump}' for people, consump in sorted_arr])
        avg = int(avg * 100) / 100

        print(f'Cidade# {case_num}:')
        print(output)
        print(f'Consumo medio: {avg:.2f} m3.')

if __name__ == '__main__':
    main()
