using System;

public static class ReverseString
{
    // For very specific cases where handling non-BMP or graphemes composed of
    // more than one codepoint is needed.
    // Because of this, it's slower.
    public static string Reverse(string input) =>
      Microsoft.VisualBasic.Strings.StrReverse(input);
}

