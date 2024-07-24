using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MethodHiding
{
    class Base
    {
        public void MyMethod()
        {
            Console.WriteLine("Base.MyMethod()");
        }
    }

    class Derived : Base
    {
       public new void MyMethod()
        {
            Console.WriteLine("Derived.MyMethod()");
        }
    }

    internal class MethodHiding
    {
        static void MainMethodHiding()
        {
            Base baseObj = new Base();
            baseObj.MyMethod();

            Derived derived = new Derived();
            derived.MyMethod();

            Base baseDerived = new Derived();
            baseDerived.MyMethod();

        }
    }
}
