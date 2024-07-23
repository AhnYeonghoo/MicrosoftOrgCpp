using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ThisContructor
{
    class MyClass
    {
        int a, b, c;

        public MyClass()
        {
            this.a = 5425;
            Console.WriteLine("MyClass()");
        }

        public MyClass(int b) : this()
        {
            this.b = b;
            Console.WriteLine("MyClass(b)");
        }

        public MyClass(int b, int c) : this(b)
        {
            this.c = c;
            Console.WriteLine($"MyClass(b) (c)");
        }

        public void PrintFields()
        {
            Console.WriteLine($"{a} {b} {c}");
        }
    }
    internal class ThisConstructor
    {
    }
}
