from collections import defaultdict

def main():
    n = int(input())
    words = []
    anagrams = defaultdict(list)

    for _ in range(n):
        word = input()
        letters = ''.join(sorted(word))
        anagrams[letters].append(word)

    res = []
    for anagram_set in anagrams.values():
        anagram_set.sort()
        res.append(anagram_set)
    res.sort(key=lambda x: x[0])

    for w in res:
        print(*w)

if __name__ == '__main__':
    main()
