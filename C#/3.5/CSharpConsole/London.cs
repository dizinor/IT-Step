using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GreatBritain
{
    class London
    {
        public int Population { get; set; }
        public London():this(2048){}
        public London(int Population)
        {
            this.Population = Population;
        }
        static public bool operator > (London first, Germany.Berlin second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (London first, Germany.Berlin second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(London first, Germany.Berlin second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(London first, Germany.Berlin second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(London first, Germany.Berlin second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(London first, Germany.Berlin second)
        {
            return first.Population != second.Population;
        }
        static public bool operator > (London first, London second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (London first, London second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(London first, London second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(London first, London second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(London first, London second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(London first, London second)
        {
            return first.Population != second.Population;
        }
        static public bool operator > (London first, Russia.Moscow second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (London first, Russia.Moscow second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(London first, Russia.Moscow second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(London first, Russia.Moscow second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(London first, Russia.Moscow second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(London first, Russia.Moscow second)
        {
            return first.Population != second.Population;
        }
    }
}
