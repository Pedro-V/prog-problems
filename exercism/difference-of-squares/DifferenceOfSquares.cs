using System;
using System.Linq;

public static class DifferenceOfSquares
{
    static int Square(int x) => x * x;

    public static int CalculateSquareOfSum(int max) =>
      Square(Enumerable.Range(1, max).Sum());

    public static int CalculateSumOfSquares(int max) =>
      Enumerable.Range(1, max).Sum(Square);

    public static int CalculateDifferenceOfSquares(int max) =>
        CalculateSquareOfSum(max) - CalculateSumOfSquares(max);
}
