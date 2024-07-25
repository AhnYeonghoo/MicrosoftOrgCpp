using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiInterfaceInheritance
{
    interface IRunnable
    {
        void Run();
    }
    interface IFlyable
    {
        void Fly();
    }

    class FlyingCar : IRunnable, IFlyable
    {
        public void Run()
        {
            Console.WriteLine("RUN()");
        }

        public void Fly()
        {
            Console.WriteLine("Fly()");
        }
    }
    internal class MultiInterfaceInheritance
    {
        static void MainMultiInterfaceInheritance()
        {
            FlyingCar car = new FlyingCar();
            car.Run();
            car.Fly();

            IRunnable run = car as IRunnable;
            run.Run();

            IFlyable fly = car as IFlyable;
            fly.Fly();
        }
    }
}
