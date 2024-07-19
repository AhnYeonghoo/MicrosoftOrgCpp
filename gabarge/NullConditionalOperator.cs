using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class NullConditionalOperator
    {
        static void MainNullConditionalOperator()
        {
            ArrayList a = null;
            a?.Add("야구");
            a?.Add("축구");
            Console.WriteLine(a?.Count);
            Console.WriteLine(a?[0]);
            Console.WriteLine(a?[1]);

            a = new ArrayList();

            a?.Add("축구");
            a?.Add("야구");
            Console.WriteLine(a?.Count);
            Console.WriteLine(a?[0]);
            Console.WriteLine(a?[1]);
        }
    }
}
