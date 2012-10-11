using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GreatBritain;
using Germany;
using Russia;
namespace CSharpConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            London l = new London();
            Moscow m = new Moscow();
            Berlin b = new Berlin();
            Console.WriteLine(l > b);
            Console.WriteLine(m == l);
        }
    }  
}
    