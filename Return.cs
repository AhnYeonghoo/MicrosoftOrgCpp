using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Return
    {
        static int Fibonacci(int n)
        {
            if (n < 2)
            {
                return n;
            }
            else
            {
                return Fibonacci(n - 1) + Fibonacci(n - 2);
            }
        }

        static void PrintProfile(string name, string phone)
        {
            if (name == "")
            {
                Console.WriteLine("이름을 입력해주세요");
                return;
            }
            Console.WriteLine($"Name: {name}, phone: {phone}");
        }

        static void MainReturn()
        {
            return;
        }
    }

    
}
