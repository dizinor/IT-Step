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
            Console.WriteLine("Введите строку:");
            string s = Console.ReadLine();
            Console.WriteLine("Введите символ");
            string c;
            try
            {
                c = Console.ReadLine();       
                if (c.Length > 2)             
                    throw new Exception("Введено больше одного символа (" + c.Length + ")");
                if (s.IndexOf(c) == -1)       
                    throw new Exception("Данного символа нет в строке");
                s = s.Replace(c, c.ToUpper());
                s = s.Remove((s.LastIndexOf(c.ToUpper())) + 1);
                Console.WriteLine(s);         
            }                                 
            catch (Exception e)               
            {
                Console.WriteLine("Ошибка: {0}", e.Message);
            }
        }

    }  
}