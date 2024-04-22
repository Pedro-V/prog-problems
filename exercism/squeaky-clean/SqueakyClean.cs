using System;
using System.Text;

// StringBuilder way.
public static class Identifier
{
    public static string Clean(string identifier)
    {
        var result = new StringBuilder(identifier.Length);
        bool mustUpper = false;
        foreach (char c in identifier) {
            if (c == ' ') result.Append('_');
            else if (c == '-') mustUpper = true;
            else if (char.IsControl(c)) result.Append("CTRL");
            else if (c >= 'α' && c <= 'ω') continue;
            else if (!char.IsLetter(c)) continue;
            else if (mustUpper) {
                result.Append(char.ToUpper(c));
                mustUpper = false;
            }
            else result.Append(c);
        }
        return result.ToString();
    }
}
