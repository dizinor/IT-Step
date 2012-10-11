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
                ar1[i] = r.Next(0,2);
            }
            foreach (int item in ar1)
                Console.Write(item + " ");
            Console.WriteLine();
            int j = 0;
            for (int i = 0; i < ar1.Length; i++)
            {
                if (ar1[i] != 0)
                {
                    ar2[j] = ar1[i];
                    j++;
                }
            }
            for (; j < ar2.Length; j++)
                ar2[j] = -1;
            foreach (int item in ar2)
                Console.Write(item + " ");
            Console.WriteLine();
        }
    }
}
