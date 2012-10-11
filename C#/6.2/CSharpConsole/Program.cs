using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    class CStack
    {
        private object[] stack;
        private int index;
        public CStack() : this(4) { }
        public CStack(int size)
        {
            stack= new object[size];
            index = 0;
        }
        public void Push(object obj)
        {
            stack[index] = obj;
            if (++index == stack.Length)
            {
                object[] temp = new object[stack.Length * 2];
                for (int i = 0; i < stack.Length; i++)
                {
                    temp[i] = stack[i];
                }
                stack = temp;
            }
        }
        public object Pop()
        {
            try
            {
                object temp = stack[--index];
                stack[index] = null;
                return temp;
            }
            catch (IndexOutOfRangeException)
            {
                index++;
                return null;
            }
        }
        public object Peek()
        {
            try
            {
                return stack[index - 1];
            }
            catch (IndexOutOfRangeException)
            {
                return null;
            }
        }
        public bool Contains(object key)
        {
            foreach (var item in stack)
            {
                if (Equals(item, key))
                    return true;
            }
            return false;
        }
        public void Clear()
        {
            stack = new object[4];
            index = 0;
        }
        public void CopyTo(object[] ar, int pos)
        {
            try
            {
                if (ar.Length < pos + index)
                    throw new ArgumentException();
                for (int i = 0; i < pos + index; i++)
                {
                    ar[pos + i] = stack[i];
                }
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Array isn't big enough for stack.");    
            }
        }
    }
    class Programm
    {
        static void Main(string[] args)
        {
            CStack s = new CStack(1);
            Console.WriteLine(s.Pop());
            Console.WriteLine(s.Peek());
            s.Push(1);
            s.Push("test");
            Console.WriteLine(s.Pop());
            Console.WriteLine(s.Peek());
            s.Push("test2");
            Console.WriteLine(s.Contains("test"));
            Console.WriteLine(s.Contains("test2"));
            s.Clear();
            Console.WriteLine(s.Peek());
            s.Push(2);
            s.Push("test3");
            object[] ar = new object[1];
            s.CopyTo(ar, 0);
            foreach (var item in ar)
            {
                Console.WriteLine(item);
            }
            ar = new object[2];
            s.CopyTo(ar, 0);
            foreach (var item in ar)
            {
                Console.WriteLine(item);
            }
        }
    }
}
