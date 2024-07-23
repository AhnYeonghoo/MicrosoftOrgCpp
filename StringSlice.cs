using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class StringSlice
    {
        static void MainStringSlice(string[] args)
        {
            string greeting = "Good Morning";

            Console.WriteLine(greeting.Substring(0, 5));
            Console.WriteLine(greeting.Substring(5));
            Console.WriteLine();

            string[] arr = greeting.Split(
                new string[] { " " }, StringSplitOptions.None);
            Console.WriteLine($"Wrod Count: {arr.Length}");
            foreach (string element in arr)
            {
                Console.WriteLine(element);
            }

            string result = (10 % 2) == 0 ? "짝수" : "홀수";
            Console.WriteLine(result);
        }
    }
}
