using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    class Program
    {
        static void ShowArray(int[,] ar, int m, int n)
        {
            Console.Write("  ");
            for (int i = 0; i < n; i++)
            {
                Console.Write(i + 1 + " ");
            }
            Console.WriteLine();
            for (int i = 0; i < m; i++)
            {
                Console.Write(i + 1 + " ");
                for (int j = 0; j < n; j++)
                {
                    Console.Write(ar[i, j] + " ");
                }
                Console.WriteLine();
            }
        }
        static void Main(string[] args)
        {
            int m, n;
            Console.Write("Введите количество строк в массиве: ");
            m = Convert.ToInt32(Console.ReadLine());
            Console.Write("Введите количество столбцов в массиве: ");
            n = Convert.ToInt32(Console.ReadLine());
            int[,] array = new int[m, n];
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    array[i, j] = j;
            ShowArray(array, m, n);
            int a, b;
            try
            {
                Console.WriteLine("Введите номер столбца, которой вы хотите переместить ");
                a = Convert.ToInt32(Console.ReadLine()) - 1;
                Console.WriteLine("Введите номер столбца, с которым вы хотите поменять");
                b = Convert.ToInt32(Console.ReadLine()) - 1;
                if (a >= n || b >= n)
                    throw new Exception("Номер столбца превышает количество столбцов.");
                int[] temp = new int[m];
                for (int i = 0; i < m; i++)
                {
                    temp[i] = array[i, a];
                    array[i, a] = array[i, b];
                    array[i, b] = temp[i];
                }
                ShowArray(array, m, n);
            }
            catch (Exception e)
            {
                Console.WriteLine("Ошибка: {0}", e.Message);
            }
            
        }

    }   
}
    