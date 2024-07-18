using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Constant
    {
        enum DialogResult { YES, NO, CANCEL, CONFIRM, OK }
        static void MainConstant()
        {
            const int MAX_INT = 2147483647;
            const int MIN_INT = -2147483648;
            Console.WriteLine(MAX_INT);
            Console.WriteLine(MIN_INT);

            Console.WriteLine((int)DialogResult.YES);
            Console.WriteLine((int)DialogResult.NO);
            Console.WriteLine((int)DialogResult.CANCEL);
            Console.WriteLine((int)DialogResult.CONFIRM);
            Console.WriteLine((int)DialogResult.OK);
        }
    }
}
