using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Cat
    {
        public string Name;
        public string Color;

        public void Meow()
        {
            Console.WriteLine($"{Name} : 야용");
        }

    }
    internal class BasicClass
    {
        static void MainBasicClass()
        {
            Cat kitty = new Cat();
            kitty.Color = "white";
            kitty.Name = "Kitty";
            kitty.Meow();
            Console.WriteLine($"{kitty.Name} : {kitty.Color}");

            Cat nero = new Cat();
            nero.Color = "Black";
            nero.Name = "Nero";
            nero.Meow();
            Console.WriteLine($"{nero.Color} : {nero.Color}");
        }

    }
}
