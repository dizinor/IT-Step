using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    abstract class GeometryFigure
    {
        protected string name;
        public double P { get; set; }
        public double S { get; set; }
        public override string ToString()
        {
            return String.Format("Фигура: {0}. Периметр фигуры = {1:f2}. Площадь фигуры = {2:f2}", name, P, S);
        }
    }
    class Triangle : GeometryFigure
    {
        Triangle(int a, int b, int c)
        {
            P = a + b + c;
            S = Math.Sqrt(P * (P - a) * (P - b) * (P - c));
            name = "треугольник";
        }
        public Triangle() : this(3, 4, 5){}
     }
    class Square : GeometryFigure
    {
        public Square(int a)
        {
            P = 4 * a;
            S = a * a;
            name = "квардрат";
        }
        public Square() : this(2){}
    }
    class Rhombus : GeometryFigure
    {
        public Rhombus(int a, int d1, int d2)
        {
            P = 4 * a;
            S = 0.5 * (d1 * d2);
            name = "ромб";
        }
        public Rhombus() : this(4, 2, 6){}
    }
    class Rectangle : GeometryFigure
    {
        public Rectangle(int a, int b)
        {
            P = 2 * (a + b);
            S = a * b;
            name = "прямоугольник";
        }
        public Rectangle() : this(2, 4){}
    }
    class Parallelogram : GeometryFigure
    {
        public Parallelogram(int a, int b, int h)
        {
            P = 2 * (a + b);
            S = a * h;
            name = "параллелограм";
        }
        public Parallelogram() : this(2,4,3){}
    }
    class Trapeze : GeometryFigure
    {
        public Trapeze(int a, int b, int c, int d, int h)
        {
            P = a + b + c + d;
            S = (0.5 * a * c) * h;
            name = "трапеция";
        }
        public Trapeze():this(2,4,4,6,3){}
    }
    class Circle : GeometryFigure
    {
        public Circle(int r)
        {
            P = 2 * Math.PI * r;
            S = Math.PI * Math.Pow(r, 2);
            name = "круг";
        }
        public Circle():this(2){}
    }
    class Ellipse : GeometryFigure
    {
        public Ellipse(int a, int b)
        {
            P = 4 * ((Math.PI * a * b + Math.Pow((a - b), 2))/(a + b));
            S = Math.PI * a * b;
            name = "эллипс";
        }
        public Ellipse():this(2, 4){}
    }
    class Program
    {
        static void Main(string[] args)
        {
            Triangle t = new Triangle();
            Square s = new Square();
            Rhombus rh = new Rhombus();
            Rectangle rect = new Rectangle();
            Parallelogram p = new Parallelogram();
            Trapeze tr = new Trapeze();
            Circle r = new Circle(20);
            Ellipse e = new Ellipse();
            Console.WriteLine(t);
            Console.WriteLine(s);
            Console.WriteLine(rh);
            Console.WriteLine(rect);
            Console.WriteLine(p);
            Console.WriteLine(tr);
            Console.WriteLine(r);
            Console.WriteLine(e);
        }
    }
}

