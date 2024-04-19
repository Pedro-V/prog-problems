using System;
using System.Linq;

public static class Bob
{
    public static string Response(string statement)
    {
        string stmt = statement.Trim();
        if (silence(stmt)) 
            return "Fine. Be that way!";
        if (question(stmt) && yelling(stmt))
            return "Calm down, I know what I'm doing!";
        if (question(stmt))
            return "Sure.";
        if (yelling(stmt))
            return "Whoa, chill out!";
        return "Whatever.";

        bool question(string s) => s.EndsWith('?');
        bool yelling(string s) => s.Any(char.IsLetter) && s.ToUpper() == s;
        bool silence(string s) => s == "";
    }
}
