using System;

class BirdCount
{
    private int[] birdsPerDay;

    public BirdCount(int[] birdsPerDay)
    {
        this.birdsPerDay = birdsPerDay;
    }

    public static int[] LastWeek() => new[] { 0, 2, 5, 3, 7, 8, 4 };

    public int Today() => birdsPerDay[^1];

    public void IncrementTodaysCount()
    {
        birdsPerDay[^1]++;
    }

    // With LINQ: birdsPerDay.Any(x => x == 0);
    public bool HasDayWithoutBirds()
    {
        foreach (int dayCount in birdsPerDay)
            if (dayCount == 0) return true;
        return false;
    }

    // With LINQ: birdsPerDay.Take(numberOfDays).Sum();
    public int CountForFirstDays(int numberOfDays)
    {
        int count = 0;
        for (int i = 0; i < numberOfDays; i++) {
            count += birdsPerDay[i];
        }
        return count;
    }

    // With LINQ: birdsPerDay.Count(x => x >= 5);
    public int BusyDays()
    {
        int n = 0;
        foreach (int dayCount in birdsPerDay) {
            if (dayCount >= 5) n++;
        }
        return n;
    }
}

