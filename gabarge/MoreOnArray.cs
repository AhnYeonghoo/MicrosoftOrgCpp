using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class MoreOnArray
    {
        private static bool CheckPassed(int score)
        {
            return score >= 60;
        }


        private static void Print(int value)
        {
            Console.WriteLine($"{value}");
        }
        static void Main()
        {
            int[] scores = new int[] { 80, 74, 81, 90, 34 };
            foreach (int score in scores)
            {
                Console.Write($"{score}");
            }
            Console.WriteLine();

            Array.Sort(scores);
            Array.ForEach<int>(scores, new Action<int>(Print));
            Console.WriteLine();

            Console.WriteLine(scores.Rank);
            Console.WriteLine(Array.BinarySearch<int>(scores, 81));

            Console.WriteLine(Array.IndexOf(scores, 90));
            Console.WriteLine(Array.TrueForAll<int>(scores, CheckPassed));

            int index = Array.FindIndex<int>(scores, (score) => score < 60);

            scores[index] = 61;
            Console.WriteLine(Array.TrueForAll<int>(scores, CheckPassed));

            Console.WriteLine(scores.GetLength(0));

            Array.Resize<int>(ref scores, 10);
            Console.WriteLine(scores.Length);

            Array.ForEach<int>(scores, new Action<int>(Print));
            Console.WriteLine();

            Array.Clear(scores, 3, 7);
            Array.ForEach<int>(scores, new Action<int>(Print));

            Console.WriteLine();
            int[] sliced = new int[3];
            Array.Copy(scores, 0, sliced, 0, 3);
            Array.ForEach<int>(sliced, new Action<int>(Print));
            Console.WriteLine();
        }
    }
}
