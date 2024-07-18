using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class SingedUnsignedConversion
    {
        static void MainSingedUnsignedConversion()
        {
            int a = 500;
            Console.WriteLine(a);

            uint b = (uint)a;
            Console.WriteLine(b);

            int x = -30;
            Console.WriteLine(x);

            uint y = (uint)x;
            Console.WriteLine(y);

            float aa = 0.9f;
            int bb = (int)aa;
            Console.WriteLine(bb);

            float cc = 1.1f;
            int dd = (int)cc;
            Console.WriteLine(dd);
        }
    }
}
