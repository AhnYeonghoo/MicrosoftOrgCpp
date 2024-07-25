using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tuple
{

    internal class Tuple
    {
        static void MainTuple()
        {
            var a = ("슈퍼맨", 9999);
            Console.WriteLine($"{a.Item1}, {a.Item2}");

            var b = (Name: "박상현", Age: 11);
            Console.WriteLine($"{b.Item1}, {b.Item2}");

            var (name, age) = b;
            Console.WriteLine($"{name}, {age}");

            var (name2, age2) = ("박문수", 34);
            Console.WriteLine($"{name2}, {age2}");

            b = a;

            Console.WriteLine($"{b.Name}, {b.Age}");

        }
    }
}
