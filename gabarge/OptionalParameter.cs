using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class OptionalParameter
    {
        static void PrintProfile(string name, string phone = "")
        {
            Console.WriteLine($"Name: {name}, Phone: {phone}");
        }

        static void MainOptionalParameter()
        {
            return;
        }
    }
}
