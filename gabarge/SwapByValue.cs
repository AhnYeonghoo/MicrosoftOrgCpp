using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class SwapByValue
    {
        public static void Swap(int a, int b)
        {
            int temp = b;
            b = a;
            a = temp;
        }

        public static void RefSwap(ref int a, ref int b)
        {
            int temp = b;
            b = a;
            a = temp;
        }

        static void MainRef()
        {
            int x = 3;
            int y = 4;

            Console.WriteLine($"{x}, {y}");
            Swap(x, y);
            Console.WriteLine($"{x}, {y}");
            RefSwap(ref x, ref y);
            Console.WriteLine($"{x}, {y}");
        }
    }
}
