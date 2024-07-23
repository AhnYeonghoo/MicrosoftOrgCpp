using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Bool
    {
        static void MainBool()
        {
            bool a = true;
            bool b = false;

            Console.WriteLine(a);
            Console.WriteLine(b);

            object c = 123;
            object d = 3.141515123541221312321m;
            object e = true;
            object f = "안녕하세요.";

            Console.WriteLine(c);
            Console.WriteLine(d);
            Console.WriteLine(e);
            Console.WriteLine(f);
        }
    }
}
