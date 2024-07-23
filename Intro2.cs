using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public struct TaggedInteger
    {
        public int Number;
        private List<string> tags;

        public TaggedInteger(int n)
        {
            Number = n;
            tags = new List<string>();
        }

        public void AddTag(string tag) => tags.Add(tag);
        public override string ToString()
        {
            return $"{Number} [{string.Join(", ", tags)}]";
        }
    }
    internal class Intro2
    {
        public static void MainIntro2()
        {
            var n1 = new TaggedInteger(0);
            n1.AddTag("A");
            Console.WriteLine(n1);

            var n2 = n1;
            n2.Number = 7;
            n2.AddTag("B");

            Console.WriteLine(n1);
            Console.WriteLine(n2);
        }
    }
}
