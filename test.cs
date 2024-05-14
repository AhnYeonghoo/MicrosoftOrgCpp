using System;
using System.Collectons.Generic;

public struct TaggedInteger
{
    public int Number;
    private List<string> tags;
    
    public TaggedInteger(int n)
    {
        Number = n;
        tags = new List<string>();
    }

    public void AddTag(string tag) => tags.Add(tag);
    public override string ToString() => $"{Number} [{string.Join(",", tags)}]";
    
}

public struct MutablePoint
{
    public int X;
    public int Y;
    
    public MutablePoint(int x, int y) => (X ,Y) = (x, y);
    public override string ToString() => $"({X}, {Y})";
}

public class Program
{
    public static void Main()
    {
        var p1 = new MutablePoint(1, 2);
        var p2 = p1;
        p2.Y = 200;
        Console.WriteLine($"{nameof(p1)} after {nameof(p2)}  is modified: {p1}}");
        Console.WriteLine($"{nameof(p2)} : {p2}");
        
        MutateAndDisplay(p2);
        Console.WriteLine($"{nameof(p2)} after passing to a method: {p2}");

        private static void MutateAndDisplay(MutablePoint p)
        {
            p.X = 100;
            Console.WriteLine($"Point mutated in a method: {p}");
        }
    }
}