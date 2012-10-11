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
            int a, b, c;
            int rectS, squareS, n, leftSpace;
            Console.WriteLine("Введите значение A");
            a = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Введите значение B");
            b = Convert.ToInt32(Console.ReadLine()); 
            Console.WriteLine("Введите значение C");
            c = Convert.ToInt32(Console.ReadLine());
            if (a == 0 || b == 0 || c == 0)
            {
                Console.WriteLine("Значения должны быть больше 0");
                return;
            }
            rectS = a * b;
            squareS = c * c;
            if (squareS > rectS)
                Console.WriteLine("Площадь квадрата больше площади прямоугольника, ни один квадрат не поместится");
            else
            {
                n = rectS / squareS;
                leftSpace = rectS % (squareS * n);
                Console.WriteLine("Квадратов помещается " + n + ". Осталось места " + leftSpace + " кв.");
            }
        }
    }
}
