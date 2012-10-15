using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleSnake
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.CursorVisible = false;
            Snake snake = new Snake(5, 5);
            snake.Print();
            while (true)
            {
                var key = Console.ReadKey().Key;
                switch (key)
                {
                    case ConsoleKey.DownArrow:
                        snake.Direction = Direction.Down;
                        break;
                    case ConsoleKey.LeftArrow:
                        snake.Direction = Direction.Left;
                        break;
                    case ConsoleKey.RightArrow:
                        snake.Direction = Direction.Right;
                        break;
                    case ConsoleKey.UpArrow:
                        snake.Direction = Direction.Up;
                        break;
                }
                snake.Move();
                snake.Print();
            }
        }
    }
}
