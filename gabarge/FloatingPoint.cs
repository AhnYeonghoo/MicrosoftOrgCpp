using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class FloatingPoint
    {
        static void MainFloatingPoint(string[] args)
        {
            float a = 3.1415_9265_3589_7932_3846f;
            Console.WriteLine(a);


            double b = 3.1415_9265_3589_7932_3846;
            Console.WriteLine(b);

            decimal c = 3.1415_9265_3589_7932_3846m;

            Console.WriteLine(c);
        }
    }
}
