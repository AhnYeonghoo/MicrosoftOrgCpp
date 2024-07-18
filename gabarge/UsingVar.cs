using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class UsingVar
    {
        static void MainUsingVar()
        {
            var a = 20;
            Console.WriteLine($"Type : {a.GetType()}, Value: {a}");

            var b = 3.1414213;
            Console.WriteLine($"Type: {b.GetType()}, Value: {b}");

            var c = "Hello World";
            Console.WriteLine($"Type: {c.GetType()}, Value: {c}");

            var d = new int[] { 10, 20, 30 };
            Console.Write($"Type: {d.GetType()}, Value: ");
            foreach (var e in d)
            {
                Console.Write(e);
            }
            Console.WriteLine();
        }
    }
}
