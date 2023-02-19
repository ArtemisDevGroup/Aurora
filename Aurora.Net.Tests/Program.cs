using Windows.System;

namespace Aurora.Net.Tests
{
    class Program
    {
        public static bool InRange(char number, char min, char max) => (number >= min) && (number <= max);

        public static bool ValidateString(string str)
        {
            foreach (char c in str)
            {
                if (!InRange(c, '0', '9')) return false;
            }
            return true;
        }

        public static bool bIsRunning = true;

        public static void ThreadMain()
        {
            while (bIsRunning)
            {
                Console.WriteLine("Thread is running!");
                Thread.Sleep(1000);
            }
        }

        public static void Main(string[] args)
        {
            Thread thread = new Thread(ThreadMain);
            thread.Start();

            Console.ReadKey();
            bIsRunning = false;

            thread.Join();

            // try
            // {
            //     int input = Convert.ToInt32(Console.ReadLine());
            // 
            //     if (input == 10) Console.WriteLine("10!");
            //     else Console.WriteLine("Not 10!");
            // }
            // catch (FormatException e)
            // {
            //     Console.WriteLine(e.Message);
            // }
        }
    }
}