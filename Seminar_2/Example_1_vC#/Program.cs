using System;
using System.Diagnostics;

namespace ACR_TEST_DELETE_ME_
{
    internal class Program
    {
        private static void Main()
        {
            var timer = new Stopwatch();
            var arr = new int[64 * 1024 * 1024];

            timer.Start();
            for (int i = 0; i < arr.Length; i++) arr[i] *= 3;
            Console.WriteLine("Loop_1: {0} ms", timer.ElapsedMilliseconds);

            timer.Restart();
            for (int i = 0; i < arr.Length; i += 16) arr[i] *= 3;
            Console.WriteLine("Loop_2: {0} ms", timer.ElapsedMilliseconds);
        }
    }
}
