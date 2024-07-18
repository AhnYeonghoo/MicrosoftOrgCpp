using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Overflow
    {
        static void MainOverflow(string[] args)
        {
            uint a = uint.MaxValue;

            Console.WriteLine(a);

            a = a + 1;

            Console.WriteLine(a);
        }
    }
}
