using System;

// Use switch expressions for the sake of readability.
public static class PlayAnalyzer
{
    public static string AnalyzeOnField(int shirtNum) => shirtNum switch {
        // Constant pattern.
        1 => "goalie",
        2 => "left back",
        // Pattern combinators.
        3 or 4 => "center back",
        5 => "right back",
        6 or 7 or 8 => "midfielder",
        9 => "left wing",
        10 => "striker",
        11 => "right wing",
        _ => throw new ArgumentOutOfRangeException(),
    };

    public static string AnalyzeOffField(object report) => report switch {
        // Type patterns.
        int amount => $"There are {amount} supporters at the match.",
        string announcement => announcement,
        // Property pattern.
        Manager { Club: null } man => man.Name,
        Manager man => $"{man.Name} ({man.Club})",
        Injury inj => $"Oh no! {inj.GetDescription()} Medics are on the field.",
        Incident inc => inc.GetDescription(),
        _ => throw new ArgumentException(),
    };
}

public class Manager
{
    public string Name { get; }

    public string? Club { get; }

    public Manager(string name, string? club)
    {
        this.Name = name;
        this.Club = club;
    }
}

public class Incident
{
    public virtual string GetDescription() => "An incident happened.";
}

public class Foul : Incident
{
    public override string GetDescription() => "The referee deemed a foul.";
}

public class Injury : Incident
{
    private readonly int player;

    public Injury(int player)
    {
        this.player = player;
    }

    public override string GetDescription() => $"Player {player} is injured.";
}
