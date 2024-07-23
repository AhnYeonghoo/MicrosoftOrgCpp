using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class FloatConversion
    {
        static void MainFloatConversion()
        {
            float a = 69.6875f;
            Console.WriteLine(a);

            double b = (double)a;
            Console.WriteLine(b);
            Console.WriteLine(69.6875 ==  b);
            Console.WriteLine(a == 69.6875);

            float x = 0.1f;
            Console.WriteLine(x);
            double y = (double)x;
            Console.WriteLine(y);

            Console.WriteLine(x == 0.1);
            Console.WriteLine(y == 0.1);
        }
    }
}
