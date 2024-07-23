using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Product
    {
        private int price = 100;

        public ref int GetPrice()
        {
            return ref price;
        }

        public void PrintPrice()
        {
            Console.WriteLine($"Price: {price}");
        }
    }
    internal class RefReturn
    {
        static void MainRefReturn()
        {
            Product carrot = new Product();
            ref int refLocalPrice = ref carrot.GetPrice();
            int normalLocalPrice = carrot.GetPrice();

            carrot.PrintPrice();
            Console.WriteLine(refLocalPrice);
            Console.WriteLine(normalLocalPrice);

            refLocalPrice = 200;

            carrot.PrintPrice();
            Console.WriteLine(refLocalPrice);
            Console.WriteLine(normalLocalPrice);
        }
    }
}
