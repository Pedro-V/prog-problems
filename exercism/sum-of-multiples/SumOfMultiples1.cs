using System;
using System.Linq;
using System.Collections.Generic;

/*
 * Mixed Collections-LINQ approach. Not very good, it's slower, verbose and a
 * bit harder to follow than other approaches.
 */

public static class SumOfMultiples
{
    public static int Sum(IEnumerable<int> multiples, int max)
    {
        var set = new HashSet<int>();
        foreach (int mult in multiples) {
            set.UnionWith(MultiplesLessThan(mult, max));
        }
        return set.Sum();
    }

    static List<int> MultiplesLessThan(int mult, int max)
    {
        var result = new List<int>();
        
        if (mult == 0) {
            result.Add(0);
            return result;
        }
    
        int i = 1, x;
        while ((x = i * mult) < max) {
            result.Add(x);
            i++;
        }
        return result;
    }
}

