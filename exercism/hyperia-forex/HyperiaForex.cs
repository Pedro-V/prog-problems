using System;

public struct CurrencyAmount
{
    private decimal amount;
    private string currency;

    public CurrencyAmount(decimal amount, string currency)
    {
        this.amount = amount;
        this.currency = currency;
    }

    private static bool SameCurrency(CurrencyAmount a, CurrencyAmount b) => 
        a.currency != b.currency ? throw new ArgumentException() : true;

    public static bool operator ==(CurrencyAmount a, CurrencyAmount b) => SameCurrency(a, b) && a.amount == b.amount;
    public static bool operator !=(CurrencyAmount a, CurrencyAmount b) => SameCurrency(a, b) && a.amount != b.amount;
    public static bool operator <(CurrencyAmount a, CurrencyAmount b) => SameCurrency(a, b) && a.amount < b.amount;
    public static bool operator >(CurrencyAmount a, CurrencyAmount b) => SameCurrency(a, b) && a.amount > b.amount;
    
    public static CurrencyAmount operator+(CurrencyAmount a, CurrencyAmount b)
    {
        SameCurrency(a, b);
        return new CurrencyAmount(a.amount + b.amount, a.currency);
    }

    public static CurrencyAmount operator-(CurrencyAmount a, CurrencyAmount b)
    {
        SameCurrency(a, b);
        return new CurrencyAmount(a.amount - b.amount, a.currency);
    }

    public static CurrencyAmount operator*(CurrencyAmount x, decimal s) => new CurrencyAmount(x.amount * s, x.currency);
    public static CurrencyAmount operator/(CurrencyAmount x, decimal s) => new CurrencyAmount(x.amount / s, x.currency);

    public static explicit operator double(CurrencyAmount x) => (double) x.amount;
    public static implicit operator decimal(CurrencyAmount x) => x.amount;
}

