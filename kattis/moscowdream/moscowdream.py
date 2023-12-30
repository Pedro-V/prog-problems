a, b, c, n = map(int, input().split())
if (
    n >= 3
    and a >= 1 and b >= 1 and c >= 1
    and (a + b + c) >= n
):
    print('YES')
else:
    print('NO')
