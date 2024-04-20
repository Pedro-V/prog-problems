using System;
using System.Linq;

public static class ReverseString
{
    // This is fast and concise for almost all cases,
    // but doesn't handle non-BMP Unicode characters.
    public static string Reverse(string input)
    {
        char[] arr = input.ToCharArray();
        Array.Reverse(arr);
        return new string(arr);
    }
}
