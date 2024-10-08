# Idea comes from: https://site.ada.edu.az/~medv/acm/Docs%20e-olimp/Volume%2061/6021_English.htm

# Basically, use two BITs to help construct prefix and suffix.
# For prefix, iterate over A, and when we are on the i-th iteration, we can determine how
# many elements before (in A) the i-th element are greater than it.
# Similarly for suffix.

class FenwickTree:
    """One-indexed Fenwick Tree/Binary Indexed Tree (BIT).

    Passed indexes (in add() and sum()) are assumed to be one-based.
    """
    def __init__(self, n):
        self.n = n + 1
        self.bit = [0] * (n + 1)

    def add(self, idx, delta=1):
        while idx < self.n:
            self.bit[idx] += delta
            idx += idx & -idx

    def sum(self, r):
        ret = 0
        while r > 0:
            ret += self.bit[r]
            r -= r & -r
        return ret

def main():
    n = int(input())
    arr = [int(c) for c in input().split()]
    pref = [0] * (n+1)
    res = 0

    f = FenwickTree(n)
    for i, x in enumerate(arr, 1):
        f.add(x)
        pref[i] = i - f.sum(x)

    f = FenwickTree(n)
    for i in reversed(range(n)):
        f.add(arr[i])
        res += pref[i+1] * f.sum(arr[i] - 1)

    print(res)

if __name__ == '__main__':
    main()

