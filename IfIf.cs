﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class IfIf
    {
        static void MainIfIf()
        {
            Console.Write("숫자를 입력하세요ㅣ ");
            string input = Console.ReadLine();
            int number = Convert.ToInt32(input);

            if (number > 0)
            {
                if (number % 2 == 0)
                {
                    Console.WriteLine("0보다 큰 짝수");
                }
                else
                {
                    Console.WriteLine("0보다 큰 홀수");
                }
            }
            else
            {
                Console.WriteLine("0보다 작거나 같은 수");
            }
        }
    }
}
