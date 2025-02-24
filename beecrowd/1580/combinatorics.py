from collections import Counter

MOD = int(1e9 + 7)
N_MAX = 1000
fact = [1] * (N_MAX + 1)
inv_fact = [1] * (N_MAX + 1)

# (a * b) % M == ((a % M) * (b % M)) % M

def precompute():
    for i in range(2, N_MAX+1):
        fact[i] = (i * fact[i -1]) % MOD
        inv_fact[i] = (pow(i, MOD - 2, MOD) * inv_fact[i-1]) % MOD

def main():
    precompute()
    while True:
        try:
            word = input()
        except EOFError:
            return
        n = len(word)
        res = fact[n]
        for i in Counter(word).values():
            res = (res * inv_fact[i]) % MOD
        print(res)

if __name__ == '__main__':
    main()
