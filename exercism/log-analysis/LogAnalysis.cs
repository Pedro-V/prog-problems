using System;

public static class LogAnalysis 
{
    public static int IndexAfter(this string s1, string s2) => s1.IndexOf(s2) + s2.Length;
    
    public static string SubstringAfter(this string log, string begin)
    {
        int i = log.IndexAfter(begin);
        return log[i..];
    }

    public static string SubstringBetween(this string log, string leftDelim, string rightDelim)
    {
        int i = log.IndexAfter(leftDelim);
        int j = log.IndexOf(rightDelim);
        return log[i..j];
    }
        
    public static string Message(this string log) => log.SubstringAfter(": ");

    public static string LogLevel(this string log) => log.SubstringBetween("[", "]");
}
