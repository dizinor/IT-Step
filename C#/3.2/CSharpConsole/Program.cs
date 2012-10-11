using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace CSharpConsole
{
    class Problem
    {
        public int A;
        public int B;
        public Problem()
        {
            A = 0;
            B = 0;
        }
        public void Parse(string s)
        {
            int pos = -1;
            try
            {
                for (int i = 0; i < s.Length; i++)
                {
                    if (s[i] == ' ' || s[i] == ',')
                    {
                        if (pos == -1)
                            pos = i;
                        else
                            throw new Exception("Неверный формат, много переменных");
                    }
                }
                if (pos == -1)
                    throw new Exception("Неверный формат, нету разделителя переменных");
                A = Convert.ToInt32(s.Substring(0, pos));
                B = Convert.ToInt32(s.Substring(pos + 1));
            }
            catch (FormatException)
            {
                Console.WriteLine("Невозможно преобразовать строку в число");
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: {0}", e.Message);
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Problem q = new Problem();
            q.Parse(Console.ReadLine());
            Console.WriteLine(q.A + " " + q.B);
        }
    }   
}
    