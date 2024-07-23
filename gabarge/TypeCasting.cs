using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TypeCasting
{

    class Mammal
    {
        public void Nurse()
        {
            Console.WriteLine("Nurse()");
        }
    }

    class Dog : Mammal
    {
        public void Bark()
        {
            Console.WriteLine("Bark()");
        }
    }

    class Cat : Mammal
    {
        public void Meow()
        {
            Console.WriteLine("Meow()");
        }
    }
    internal class TypeCasting
    {
        static void MainTypeCasting()
        {
            Mammal mam = new Dog();
            Dog dog;

            if (mam is Dog)
            {
                dog = (Dog)mam;
                dog.Bark();
            }

            Mammal mam2 = new Cat();

            Cat cat = mam2 as Cat;
            if (cat != null)
            {
                cat.Meow();
            }
            else
            {
                Console.WriteLine("Cat2 is not a Cat");
            }

            Cat cat2 = mam as Cat;
            if (cat2 != null)
            {
                cat.Meow();
            }
            else
            {
                Console.WriteLine("cat2 is not a Cat");
            }

        }
    }
}
