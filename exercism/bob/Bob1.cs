using System.Linq;

// A more declarative and efficient approach.
public static class Bob
{
    public static string Response(string statement)
    {
        var input = statement.TrimEnd();
        if (input == "") return "Fine. Be that way!";

        bool IsShout = input.Any(char.IsLetter) && input.ToUpper() == input;
        return (input.EndsWith('?'), IsShout) switch {
            (true, true) => "Calm down, I know what I'm doing!",
            (_, true)    => "Whoa, chill out!",
            (true, _)    => "Sure.",
            _            => "Whatever.",
        };
    }
}
