using System;

namespace VariablesDemo
{
    class Program
    {
        static void MainVariableDemo(string[] args)
        {
            string name = "홍길동";
            char exmark = '!';
            sbyte age;
            age = 20;

            Console.WriteLine($"Hello {name + exmark}");
            Console.WriteLine($"You are {age} years old {exmark}");
        }
    }
}