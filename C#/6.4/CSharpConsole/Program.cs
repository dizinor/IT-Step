using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    class Point2D<T>
    {
        T x;
        T y;
        public T X { get { return x; } set { x = value; } }
        public T Y { get { return y; } set { y = value; } }
        public Point2D() : this(default(T), default(T)) { }
        public Point2D(T x, T y)
        {
            this.x = x;
            this.y = y;
        }
    }
    class Point3D : Point2D<int>
    {
        int z;
        public int Z { get { return z; } set { z = value; } }
        public Point3D() : this(default(int), default(int), default(int)) { }
        public Point3D(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }
        public override string ToString()
        {
            return String.Format("X={0}, Y={1}, Z={2}", X, Y, Z);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Point3D p = new Point3D();
            Console.WriteLine(p);
        }
    }
}

