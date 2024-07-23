using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Constructor
{
    class Cat
    {
        public Cat()
        {
            Name = "";
            Color = "";
        }

        public string Name;
        public string Color;

        public Cat(string Name, string Color)
        {
            this.Name = Name;
            this.Color = Color;
        }

        ~Cat()
        {
            Console.WriteLine($"{Name} : 잘가");
        }

        public void Meow()
        {
            Console.WriteLine($"{Name} : 야옹");
        }
    }

    internal class Constructor
    {
        static void MainConstructor()
        {
            Cat kitty = new Cat("키디", "하얀색");
            Cat nero = new Cat("네로", "검정색");
            kitty.Meow();
            Console.WriteLine($"{kitty.Name} : {kitty.Color}");
            nero.Meow();
            Console.WriteLine($"{nero.Name} : {nero.Color}");
        }
    }
}
