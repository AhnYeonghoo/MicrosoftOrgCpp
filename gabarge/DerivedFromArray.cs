using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class DerivedFromArray
    {
        static void MainDerivedFromArray()
        {
            int[] array = new int[] { 10, 30, 20, 7, 1 };
            Console.WriteLine(array.GetType());
            Console.WriteLine(array.GetType().BaseType);
        }
    }
}
