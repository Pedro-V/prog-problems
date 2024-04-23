using System;
using System.Collections.Generic;
using System.Linq;

public record struct Coord(ushort X, ushort Y)
{
    public int Length => Math.Abs(X - Y);
}

public record struct Plot(Coord P1, Coord P2, Coord P3, Coord P4)
{
    public int LongestSide => new[] { P1, P2, P3, P4 }.Max(c => c.Length);
}

public class ClaimsHandler
{
    private Stack<Plot> claims = new();
    
    public void StakeClaim(Plot plot) => claims.Push(plot);

    public bool IsClaimStaked(Plot plot) => claims.Contains(plot);

    public bool IsLastClaim(Plot plot) => claims.Peek() == plot;

    public Plot GetClaimWithLongestSide() => claims.MaxBy(p => p.LongestSide);

}
