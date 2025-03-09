from math import ceil

class Solution(object):
    def repeatedStringMatch(self, a, b):
        n = len(a)
        m = len(b)
        k = ceil(m / n)
        if b in a*k:
            return k
        elif b in a*(k+1):
            return k + 1
        else:
            return -1
