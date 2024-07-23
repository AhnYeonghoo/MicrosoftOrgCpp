using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Console;
namespace ConsoleApp1
{
    internal class StringSearch
    {
        static void MainStringSearch()
        {
            string greeting = "Good Morning";
            Console.WriteLine(greeting);
            Console.WriteLine();

            WriteLine($"IndexOf 'Good' : {greeting.IndexOf("Good")}");
            WriteLine($"IndexOf 'o' : {greeting.IndexOf("o")}");

            // LastIndexOf
            WriteLine($"LastIndexOf 'Good' : {greeting.LastIndexOf("Good")}");
            WriteLine($"LastIndexOf 'o' : {greeting.LastIndexOf("o")}");

            // StartsWith
            WriteLine($"StartsWith 'Good' : {greeting.StartsWith("good")}");
            WriteLine($"StartsWith 'Morning' : {greeting.StartsWith("morning")}");

            // EndsWith
            WriteLine($"EndsWith 'Good' : {greeting.EndsWith("Good")}");
            WriteLine($"EndsWith 'o' : {greeting.EndsWith("o")}");

            // Contains
            WriteLine($"Contains 'Evening' : {greeting.Contains("Evening")}");
            WriteLine($"Contains 'Morning' : {greeting.Contains("Morning")}");

            // Replace
            WriteLine($"Replaced 'Morning' with 'Evening' : {greeting.Replace("Morning", "Evening")}");

            
        }
    }
}
