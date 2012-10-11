using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    class Student
    {
        private string firstName;
        private string lastName;
        private string group;
        private int age;
        private int[][] marks;
        private int progMark;
        private int admMark;
        private int desMark;
        private int Count(int[] marks)
        {
            int n = 0;
            foreach (var item in marks)
                n++;
            return n;
        }
        private void AddMark(int[][] dest, int[][] src)
        {
            for (int i = 0; i < dest.Length; i++)
            {
                for (int j = 0; j < dest[i].Length; j++)
                {
                    dest[i][j] = src[i][j];
                }
            }
        }
        private void ShowMarks(int[] marks)
        {
            foreach (var item in marks)
            {
                Console.Write(Convert.ToString(item) + " ");
            }
        }
        public void ShowMarks(int i)
        {
            foreach (var item in marks[i])
            {
                Console.Write(Convert.ToString(item) + " ");
            }
        }
        public void SetMarks(int value)
        {
            for (int i = 0; i < marks[value].Length; i++)
            {
                marks[value][i] = Convert.ToInt32(Console.ReadLine());
            }
        }
        private int AverageMark(int[] marks)
        {
            int result = 0;
            int n = 0;
            foreach (int item in marks)
            {
                result += item;
                n++;
            }
            return result / n;
        }
        public int AverageMark(int value)
        {
            int result = 0;
            int n = 0;
            foreach (var item in marks[value])
            {
                result += item;
                n++;
            }
            return n;
        }
        public Student():this("Vasya", "Pupkin", "1A", 15, new int[]{2,4,4}, new int[]{3,3,3}, new int[]{4,5,5}){}
        public Student(string firstName, string lastName, string group, int age, int[] progMark, int[] admMark, int[] desMark)
        {
            this.firstName = firstName;
            this.lastName = lastName;
            this.group = group;
            this.age = age;
            marks = new int[3][];
            marks[0] = new int[Count(progMark)];
            marks[1] = new int[Count(admMark)];
            marks[2] = new int[Count(desMark)];
            AddMark(marks, new int[3][]{progMark, admMark, desMark});
            this.progMark = AverageMark(marks[0]);
            this.admMark = AverageMark(marks[1]);
            this.desMark = AverageMark(marks[2]);
        }
        public void Show()
        {
            Console.WriteLine("Имя студента: {0} {1}", firstName, lastName);
            Console.WriteLine("Группа {0}. Возраст {1}", group, age);
            Console.Write("Оценки по программированию ");
            ShowMarks(marks[0]);
            Console.WriteLine("Средняя оценка по программированию {0}", AverageMark(marks[0]));
            Console.Write("Оценки по администрированию ");
            ShowMarks(marks[1]);
            Console.WriteLine("Средняя оценка по администрированию {0}", AverageMark(marks[1]));
            Console.Write("Оценки по программированию ");
            ShowMarks(marks[2]);
            Console.WriteLine("Средняя оценка по дизайну {0}", AverageMark(marks[2]));
        }
    }
    class Program
    {
        static void StudentMenu(Student a)
        {
            string option;
            bool isExit = false;
            while (!isExit)
            {
                Console.WriteLine("Выберите пункт меню:");
                Console.WriteLine("1. Показать всю информацию о студенте");
                Console.WriteLine("2. Показать оценки по программированию");
                Console.WriteLine("3. Поставить оценки по программированию");
                Console.WriteLine("4. Показать оценки по администрированию");
                Console.WriteLine("5. Поставить оценки по администрированию");
                Console.WriteLine("6. Показать оценки по дизайну");
                Console.WriteLine("7. Поставить оценки по дизайну");
                Console.WriteLine("8. Показать среднюю оценку по программированию");
                Console.WriteLine("9. Показать среднюю оценку по администрированию");
                Console.WriteLine("0. Показать среднюю оценку по дизайну");
                Console.WriteLine("Или любую другую клавишу, чтобы выйти");
                option = Console.ReadLine();
                switch (option)
                {
                    case "1":
                        a.Show();
                        break;
                    case "2":
                        a.ShowMarks(0);
                        break;
                    case "3":
                        a.SetMarks(0);
                        break;
                    case "4":
                        a.ShowMarks(1);
                        break;
                    case "5":
                        a.SetMarks(1);
                        break;
                    case "6":
                        a.ShowMarks(2);
                        break;
                    case "7":
                        a.SetMarks(2);
                        break;
                    case "8":
                        Console.WriteLine("Средняя оценка по программированию {0}", a.AverageMark(0));
                        break;
                    case "9":
                        Console.WriteLine("Средняя оценка по администрированию {0}", a.AverageMark(1));
                        break;
                    case "0":
                        Console.WriteLine("Средняя оценка по дизайну {0}", a.AverageMark(2));
                        break;
                    default:
                        isExit = true;
                        break;
                }
                Console.ReadLine();
                Console.Clear();
            }
        }
        static void Main(string[] args)
        {
            Student a = new Student();
            StudentMenu(a);
        }
    }  
}
    