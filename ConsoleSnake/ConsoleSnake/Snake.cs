using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleSnake
{
    class Snake
    {
        private List<Segment> segments;
        private int appleX;
        private int appleY;
        private Random rnd;
        private const int HEIGHT = 20;
        private const int WIDTH = 40;


        public Direction Direction { get; set; }
        public Snake(int x, int y)
        {
            segments = new List<Segment>();
            segments.Add(new Segment(x, y));
            Direction = Direction.Up;
            rnd = new Random(DateTime.Now.Millisecond);
            Console.SetWindowSize(WIDTH, HEIGHT);
            Console.SetBufferSize(WIDTH, HEIGHT);
            SpawnApple();
        }
        public int Size 
        {
            get
            {
                return segments.Count;
            }
        }
        public Segment this[int index]
        {
            get
            {
                return segments[index];
            }
        }
        public void Move()
        {
            int x = 0, y = 0;
            switch (Direction)
            {
                case Direction.Up:
                    if (segments[0].Y > 0)
                        y = -1;
                    break;
                case Direction.Right:
                    if (segments[0].X < WIDTH - 1)
                        x = 1;
                    break;
                case Direction.Down:
                    if (segments[0].Y < HEIGHT - 1)
                        y = 1;
                    break;
                case Direction.Left:
                    if (segments[0].X > 0) 
                        x = -1;
                    break;
            }
            for (int i = Size - 1; i >= 1; i--)
            {
                segments[i].X = segments[i - 1].X;
                segments[i].Y = segments[i - 1].Y;
            }
            segments[0].X += x;
            segments[0].Y += y;
            if (segments[0].X == appleX && segments[0].Y == appleY)
            {
                segments.Add(new Segment(appleX, appleY));
                SpawnApple();
            }
        }
        public void Print()
        {
            Console.Clear();
            for (int i = Size - 1; i >= 0; i--)
            {
                Console.SetCursorPosition(segments[i].X, segments[i].Y);
                Console.Write((i == 0) ? '@' : '8');
            }
            Console.SetCursorPosition(appleX, appleY);
            Console.Write('*');
        }
        private void ClrScr()
        {
            for (int i = 1; i < WIDTH - 2; i++)
                for (int j = 1; j < HEIGHT - 3; j++)
                {
                    Console.SetCursorPosition(i, j);
                    Console.Write((char)0);
                }
        }
        private bool IsFree(int x, int y)
        {
            foreach (var item in segments)
            {
                if (x == item.X && y == item.Y)
                    return false;
            }
            return true;
        }
        private void SpawnApple()
        {
            do
            {
                appleX = rnd.Next(WIDTH);    
                appleY = rnd.Next(HEIGHT);
            }
            while (!IsFree(appleX, appleY));
        }
    }
    class Segment
    {
        public Segment(int x = 0, int y = 0)
        {
            X = x;
            Y = y;
        }
        public int X { get; set; }
        public int Y { get; set; }
    }
    enum Direction
    {
        Up,
        Right,
        Down,
        Left
    }
}
