using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    public delegate bool Searcher(object obj, object key);
    class Program
    {
        static public bool IsIt(object obj, object key)
        {
            return Equals(obj, key);
        }
        static public int Search(object[] ar, object key, Searcher s)
        {
            for (int i = 0; i < ar.Length; i++)
            {
                if (s(ar[i], key))
                    return i;
            }
            return -1;
        }
        static void Main(string[] args)
        {
            object[] ar = new object[] { 0, 1, 2, 3, 4 };
            int result = Search(ar, 1, new Searcher(IsIt));
            if (result == -1)
                Console.WriteLine("Элемент не найден");
            else
                Console.WriteLine("Элемент найден на позиции " + result);
        }
    }
}

