class FenwickTree:
    """One-indexed Fenwick Tree/Binary Indexed Tree (BIT)."""
    def __init__(self, n):
        self.n = n + 1
        self.bit = [0] * (n + 1)

    @classmethod
    def from_list(cls, a):
        obj = cls(len(a))
        for i, val in enumerate(a, start=1):
            obj.add(i, val)
        return obj

    def lsb(self, i):
        return i & -i

    def add(self, idx, delta):
        while idx < self.n:
            self.bit[idx] += delta
            idx += self.lsb(idx)

    def sum(self, a, b=None):
        if b is None:
            return self._prefix_sum(a)
        return self._prefix_sum(a) - self._prefix_sum(b - 1)

    def _prefix_sum(self, r):
        ret = 0
        while r > 0:
            ret += self.bit[r]
            r -= self.lsb(r)
        return ret

def main():
    n, q = map(int, input().split())
    arr = [int(c) for c in input().split()]
    f = FenwickTree.from_list(arr)
    for _ in range(q):
        op, *operands = map(int, input().split())
        if op == 0:
            k, new_p = operands
            old_p, arr[k-1] = arr[k-1], new_p
            f.add(k, -old_p + new_p)
        if op == 1:
            k, = operands
            print(f.sum(k))

if __name__ == '__main__':
    main()
