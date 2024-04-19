using System;

static class AssemblyLine
{
    public static double SuccessRate(int speed) => speed switch {
            0   =>   0,
            < 5 =>   1,
            < 9 =>  .9,
            9   =>  .8,
            10  => .77,
            _   => -1,
    };
    
    public static double ProductionRatePerHour(int speed) =>
        (speed * 221) * SuccessRate(speed);

    public static int WorkingItemsPerMinute(int speed) =>
        (int) Math.Floor(ProductionRatePerHour(speed) / 60);
}

