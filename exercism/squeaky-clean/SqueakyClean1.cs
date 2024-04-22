using System;
using System.Text.RegularExpressions;

// Regex-based way.
public static class Program
{
    public static string Clean(string identifier)
    {
        identifier = Regex.Replace(identifier, @"\s", "_");
        identifier = Regex.Replace(identifier, @"\0", "CTRL");
        identifier = Regex.Replace(identifier, @"-\D", new MatchEvaluator(ToCamelCase));
        return Regex.Replace(identifier, @"[α-ω]|\d|\W", "");
    }

    private static string ToCamelCase(Match match) => match.Value[1].ToString().ToUpper();
}

