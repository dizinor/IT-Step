using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            uint a, b;
            Console.WriteLine("Введите первое число.");
            a = Convert.ToUInt32(Console.ReadLine());
            Console.WriteLine("Введите второе число.");
            b = Convert.ToUInt32(Console.ReadLine());
            if (a > b)
            {
                b += a;
                a = b - a;
                b -= a;
            }
            for (uint i = a; i <= b; i++)
            {
                for (uint j = 0; j < i; j++)
                    Console.Write(i);
                Console.WriteLine();
            }
        }
    }
}
