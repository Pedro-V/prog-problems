using System;

public class Player
{
    public int RollDie()
    {
        var die = new Random();
        return die.Next(1, 19);
    }

    public double GenerateSpellStrength()
    {
        var die = new Random();
        return die.NextDouble() * 100;
    }
}

