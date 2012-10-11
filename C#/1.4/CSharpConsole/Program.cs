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
            int n;
            n = Convert.ToInt32(Console.ReadLine());
            int k;
            k = 0;
            while (n>9)
            {
                k += n % 10;
                n /= 10;
                k *= 10;
            }
            k += n;
            Console.WriteLine(k);
        }
    }
}
