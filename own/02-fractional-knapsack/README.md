# [Bounded] Fractional Knapsack

## Description

You're given $n$ items, each with a weight and value, and a knapsack with a capacity of $m$.

Each item can be chosen only once, but a part of the item can be selected, with its value calculated based on the proportion of the weight chosen. What is the maximum value of the items in the knapsack under the limited capacity?

# Input/Output

The first line contains the number of test cases. Each test case begins with a
line containing two integers, $n$ and $m$. Then follows $n$ lines. The $i$-th line
has two integers, $w$ and $v$, the weight and value of the $i$-th item.

The output, for each test case, is the maximum value for the knapsack given
the constraints, printed in a line by itself, with 2 decimal houses of
precision, rounding up.

## Sample 1

### Input

```
3
5 50
10 50
20 120
30 150
40 210
50 240
3 50
20 100
10 60
30 120
2 10
5 100
5 90
```

### Output

```
277.50
240.00
190.00
```
