using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class LocalFunction
    {
        static string ToLowerString(string input)
        {
            var arr = input.ToCharArray();
            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = ToLowerChar(i);
            }

            char ToLowerChar(int i)
            {
                if (arr[i] < 65 || arr[i] > 90)
                {
                    return arr[i];
                }
                else
                {
                    return (char)(arr[i] + 32);
                }
            }
            return new string(arr);
        }

        static void MainLocalFunction()
        {
            Console.WriteLine(ToLowerString("hello"));
            Console.WriteLine(ToLowerString("Good Morning"));
        }
    }
}
