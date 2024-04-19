class Lasagna
{
    public int ExpectedMinutesInOven() => 40;

    public int RemainingMinutesInOven(int minutes) => ExpectedMinutesInOven() - minutes;

    public int PreparationTimeInMinutes(int layers) => layers * 2;

    public int ElapsedTimeInMinutes(int layers, int minutes)
    {
      return PreparationTimeInMinutes(layers) + minutes;
    }
}

