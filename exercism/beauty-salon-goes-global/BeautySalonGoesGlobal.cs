using System;
using System.Globalization;

public enum Location
{
    NewYork,
    London,
    Paris
}

public enum AlertLevel
{
    Early,
    Standard,
    Late
}

public static class Appointment
{
    private static bool isWindows = OperatingSystem.IsWindows();

    public static string GetTimeZoneID(Location loc) => loc switch {
        Location.NewYork => isWindows ? "Eastern Standard Time" : "America/New_York",
        Location.London => isWindows ? "GMT Standard Time" : "Europe/London",
        Location.Paris => isWindows ? "W. Europe Standard Time" : "Europe/Paris",
    };

    public static TimeZoneInfo GetTimeZoneInfo(Location loc) =>
        TimeZoneInfo.FindSystemTimeZoneById(GetTimeZoneID(loc));
    
    public static DateTime ShowLocalTime(DateTime dtUtc) => dtUtc.ToLocalTime();

    public static DateTime Schedule(string appointmentDateDescription, Location location)
    {
        TimeZoneInfo tz = GetTimeZoneInfo(location);
        DateTime dt = DateTime.Parse(appointmentDateDescription);
        return TimeZoneInfo.ConvertTimeToUtc(dt, tz);
    }

    public static DateTime GetAlertTime(DateTime appointment, AlertLevel alertLevel) => alertLevel switch {
        AlertLevel.Early => appointment.AddDays(-1),
        AlertLevel.Standard => appointment.AddHours(-1).AddMinutes(-45),
        AlertLevel.Late => appointment.AddMinutes(-30),
    };

    public static bool HasDaylightSavingChanged(DateTime dt, Location location)
    {
        var tz = GetTimeZoneInfo(location);
        var before = dt.AddDays(-7);
        return tz.IsDaylightSavingTime(dt) != tz.IsDaylightSavingTime(before);
    }

    public static DateTime NormalizeDateTime(string dtStr, Location location)
    {
        string cultureName = location switch {
            Location.NewYork => "en-US",
            Location.London => "en-GB",
            Location.Paris => "fr-FR",
        };
        CultureInfo culture = new CultureInfo(cultureName);
        bool success = DateTime.TryParse(dtStr, culture, out var result);
        return success ? result : DateTime.MinValue;
    }
}

