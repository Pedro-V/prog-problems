using System;

enum LogLevel
{
    Unknown,
    Trace,
    Debug,
    Info = 4,
    Warning,
    Error,
    Fatal = 42,
}

static class LogLine
{
    public static LogLevel ParseLogLevel(string logLine)
    {
        string abbreviation = logLine[1..4];
        return abbreviation switch {
            "TRC" => LogLevel.Trace,
            "DBG" => LogLevel.Debug,
            "INF" => LogLevel.Info,
            "WRN" => LogLevel.Warning,
            "ERR" => LogLevel.Error,
            "FTL" => LogLevel.Fatal,
            _     => LogLevel.Unknown,
        };
    }

    public static string OutputForShortLog(LogLevel logLevel, string message) =>
        $"{(int) logLevel}:{message}";
}

