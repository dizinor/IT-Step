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
            Single cash = 1000;
            int k = 0;
            Console.WriteLine("Введите процент увеличения суммы, от 0 до 25");
            Single p = Convert.ToSingle(Console.ReadLine());
            if (p < 0 || p > 25)
            {
                Console.WriteLine("Введен неправильный процент");
                return;
            }
            while (cash < 1100)
            {
                cash *= (1 + p / 100);
                k++;
            }
            Console.WriteLine("Через " + k + " месяц(ев), вклад составит " + cash);
        }
    }
}
