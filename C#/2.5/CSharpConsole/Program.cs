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
            Console.WriteLine("Введите строку");
            string s = Console.ReadLine();
            int letters = 0;
            int UpCase = 0;
            int LowCase = 0;
            int Digits = 0;
            int Space = 0;
            int Symbs = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] >= 'A' && s[i] <= 'Z')
                    UpCase++;
                if (s[i] >= 'a' && s[i] <= 'z')
                    LowCase++;
                if (s[i] == ' ')
                    Space++;
                if (s[i] >= '0' && s[i] <= '9')
                    Digits++;
            }
            letters = UpCase + LowCase;
            Symbs = s.Length - letters - Digits - Space;
            Console.WriteLine("Количество символов " + s.Length);
            Console.WriteLine("Количество букв " + letters);
            Console.WriteLine("Букв в верхнем регистре " + UpCase);
            Console.WriteLine("Букв в нижнем регистре " + LowCase);
            Console.WriteLine("Количество цифр " + Digits);
            Console.WriteLine("Количество пробелов " + Space);
            Console.WriteLine("Остальные символы " + Symbs);
        }
    }
}