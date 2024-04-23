using System;
using System.Text.RegularExpressions;

public class LogParser
{
    public bool IsValidLine(string text) => Regex.IsMatch(text, @"^\[(TRC|DBG|INF|WRN|ERR|FTL)\]");

    public string[] SplitLogLine(string text) => Regex.Split(text, @"<[\^*=-]*>");

    public int CountQuotedPasswords(string lines) => Regex.Count(lines,"\".*password.*\"", RegexOptions.IgnoreCase);

    public string RemoveEndOfLineText(string line) => Regex.Replace(line, @"end-of-line\d*", "");

    public string[] ListLinesWithPasswords(string[] lines)
    {
        Regex reg = new Regex(@"\bpassword\w+\b", RegexOptions.IgnoreCase);
        string[] result = new string[lines.Length];
        for (int i = 0; i < lines.Length; i++) {
            string match = reg.Match(lines[i]).Value;
            string prefix = match == "" ? "--------" : match;
            result[i] = $"{prefix}: {lines[i]}";
        }
        return result;
    }
}
