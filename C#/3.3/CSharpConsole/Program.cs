using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    class Problem
    {
        private int a1, a2, b1, b2, c1, c2;
        private int x, y;
        public Problem()
        {
            try
            {
                Console.WriteLine("Введите коэффициенты первого уравнения");
                a1 = Convert.ToInt32(Console.ReadLine());
                b1 = Convert.ToInt32(Console.ReadLine());
                c1 = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("Введите коэффициенты второго уравнения");
                a2 = Convert.ToInt32(Console.ReadLine());
                b2 = Convert.ToInt32(Console.ReadLine());
                c2 = Convert.ToInt32(Console.ReadLine());
            }
            catch (FormatException)
            {
                Console.WriteLine("Введено не число");
            }
        }
        public int[] Solve()
        {
            try
            {
                //a1x + b1y = c1;
                //a2x + b2y = c2;
                //x = (c1 - b1y) / a1;
                //a2 * ((c1 - b1y) / a1) + b2y = c2;
                //a2 * (c1 - b1y) + a1b2y = a1c2;
                //a2c1 - a2b1y + a1b2y = a1c2;
                //a1b2y - a2b1y = a1c2 - a2c1;
                //y * (a1b2 - a2b1) = a1c2 - a2c1;
                //y = (a1c2 - a2c1) / (a1b2 - a2b1);
                y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
                x = (c1 - b1 * y) / a1;
                return new int[] { x, y };
            }
            catch (DivideByZeroException)
            {
                throw new ArgumentOutOfRangeException();
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Problem q = new Problem();
            try
            {
                foreach (var item in q.Solve())
                {
                    Console.WriteLine("Корень уравнения " + item);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }  
}
    