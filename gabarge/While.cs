using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class While
    {
        static void MainWhile()
        {
            int i = 10;
            while (i > 0)
            {
                Console.WriteLine($"i : {i--}");
            }
        }
    }
}
