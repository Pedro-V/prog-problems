using System;

public static class CentralBank
{
    public static string DisplayDenomination(long @base, long multiplier)
    {
        try {
            long result = checked(@base * multiplier);
            return result.ToString();
        } catch (OverflowException)
            return "*** Too Big ***";
    }

    public static string DisplayGDP(float @base, float multiplier)
    {
        float result = @base * multiplier;
        return float.IsFinite(result) ? result.ToString() : "*** Too Big ***";
    }

    public static string DisplayChiefEconomistSalary(decimal salaryBase, decimal multiplier)
    {
        try {
            decimal result = checked(salaryBase * multiplier);
            return result.ToString();
        } catch (OverflowException)
            return "*** Much Too Big ***";
    }
}
