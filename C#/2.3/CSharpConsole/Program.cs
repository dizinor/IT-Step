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
            Random r = new Random();
            Console.WriteLine("Введите размер массива");
            int a = Convert.ToInt32(Console.ReadLine());
            int[] ar1 = new int[a];
            int[] ar2 = new int[a];
            for (int i = 0; i < ar1.Length; i++)
            {
                ar1[i] = r.Next(-5, 5);
            }
            foreach (int item in ar1)
                Console.Write(item + " ");
            Console.WriteLine();
            Console.WriteLine("Введите искомое число");
            int b = Convert.ToInt32(Console.ReadLine());
            int k = 0;
            foreach (int item in ar1)
            {
                if (item == b)
                    k++;
            }
            Console.WriteLine("Число " + b + " в массиве встретилось " + k + " раз(а).");
        }
    }
}