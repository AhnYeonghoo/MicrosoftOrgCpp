using System;


namespace Program
{
    class Program
    {
        static void MainProgram()
        {
            string timeIn = DateTime.Now.ToString("yyyy-mm-dd:mm:ss");

            int RegularParking = CheckRegularParking();

            if (RegularParking == 1)
            {
                GateOpen();
            }
            else
            {
                PrintTicket(timeIn);
                GateOpen();
            }
        }

        static int CheckRegularParking()
        {
            int result;
            bool IsRegistered = false;

            if (IsRegistered == true)
            {
                result = 1;
                return result;
            }
            else
            {
                result = 2;
                return result;
            }
        }

        static void GateOpen()
        {
            Console.WriteLine("차단기가 열립니다.");
        }

        static void PrintTicket(string time)
        {
            Console.WriteLine("입차시간: {0}", time);
        }
    }
}