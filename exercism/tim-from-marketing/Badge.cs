using System;

static class Badge
{
    public static string Print(int? id, string name, string? department)
    {
        string dep = (department ?? "owner").ToUpper();
        return id.HasValue switch {
          true  => $"[{id}] - {name} - {dep}",
          false => $"{name} - {dep}",
        };
    }
}
