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
                ar1[i] = r.Next(-5,5);
            }
            foreach (int item in ar1)
                Console.Write(item + " ");
            Console.WriteLine();
            int temp;
            for (int i = 0; i < ar1.Length; i++)
            {
                 for(int j = ar1.Length - 1; j > i; j--)
                 {
                     if (ar1[j - 1] > ar1[j])
                     {
                         temp = ar1[j - 1];
                         ar1[j - 1] = ar1[j];
                         ar1[j] = temp;
                     }
                 }
            }
            foreach (int item in ar1)
                Console.Write(item + " ");
            Console.WriteLine();
        }
    }
}
