# Coin Change

## Description

Given $n$ coin sizes and an integer amount $amt$, find the combination of coin sizes
whose sum equals $amt$ and is minimal in size.

If no such combination is possible, return -1.

## Input/Output

The first line gives an integer, the number of test cases. For each test case,
the first line has integers $n$ and $amt$, the number of coin sizes and the
target amount. The follows a line with $n$ space-separated integers, the sizes
of the coins.

The ouput should be a line for each test case, cointaining the answer.

## Sample 1

### Input

```
3
6 131
1 5 10 20 50 100
3 60
1 20 50
3 98
1 49 50
1 10
10
```

### Output

```
4
3
2
1
```
