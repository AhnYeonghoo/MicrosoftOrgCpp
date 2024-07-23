using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class CTS
    {
        static void MainCTS(string[] args)
        {
            System.Int32 a = 123;
            int b = 456;
            Console.WriteLine($"a Type: {a.GetType().ToString()}, Value: {a}");
            Console.WriteLine($"b Type: {b.GetType().ToString()}, Value: {b}");

            System.String c = "abc";
            string d = "Def";

            Console.WriteLine($"c Type: {c.GetType().ToString()}, Value: {c}");
            Console.WriteLine($"d Type: {d.GetType().ToString()}, Vaalue: {d}");
        }
    }
}
