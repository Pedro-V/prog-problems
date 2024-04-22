using System;
using System.Collections.Generic;
using System.Linq;

// LINQ-based with switch expression.
public static class ProteinTranslation
{
    static string aminoAcid(string codon) => codon switch {
        "AUG" => "Methionine",
        "UUU" or "UUC" => "Phenylalanine",
        "UUA" or "UUG" => "Leucine",
        "UCU" or "UCC" or "UCA" or "UCG" => "Serine",
        "UAU" or "UAC" => "Tyrosine",
        "UGU" or "UGC" => "Cysteine",
        "UGG" => "Tryptophan",
        "UAA" or "UAG" or "UGA" => "STOP",
        _ => throw new Exception("Invalid sequence"),
    };
    
    public static string[] Proteins(string strand) =>
        Enumerable
            .Range(0, strand.Length / 3)
            .Select(i => strand.Substring(i * 3, 3))
            .TakeWhile(x => aminoAcid(x) != "STOP")
            .Select(x => aminoAcid(x))
            .ToArray();
}
