using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    
    class Program
    {
        static void Calc(Dictionary<string, int> dic, string text)
        {
            string[] temp = text.Split(new char[] {' ', ',', '.' });
            for (int i = 0; i < temp.Length; i++)
                temp[i] = temp[i].ToLower();
            foreach (var item in temp)
            {
                if (item == "")
                    continue;
                if (dic.ContainsKey(item))
                    dic[item] += 1;
                else
                    dic.Add(item, 1);
            }
        }
        static void Main(string[] args)
        {
            string text = "One, two, three, check. One, two. Check, check.";
            Dictionary<string, int> dic = new Dictionary<string, int>();
            Calc(dic, text);
            foreach (var item in dic)
            {
                Console.WriteLine(item);
            }
        }
    }
}

