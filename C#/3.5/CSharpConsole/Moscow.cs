using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Russia
{
    class Moscow
    {
        public int Population { get; set; }
        public Moscow():this(8192){}
        public Moscow(int Population)
        {
            this.Population = Population;
        }
        static public bool operator > (Moscow first, Germany.Berlin second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (Moscow first, Germany.Berlin second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(Moscow first, Germany.Berlin second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(Moscow first, Germany.Berlin second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(Moscow first, Germany.Berlin second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(Moscow first, Germany.Berlin second)
        {
            return first.Population != second.Population;
        }
        static public bool operator > (Moscow first, GreatBritain.London second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (Moscow first, GreatBritain.London second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(Moscow first, GreatBritain.London second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(Moscow first, GreatBritain.London second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(Moscow first, GreatBritain.London second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(Moscow first, GreatBritain.London second)
        {
            return first.Population != second.Population;
        }
        static public bool operator > (Moscow first, Moscow second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (Moscow first, Moscow second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(Moscow first, Moscow second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(Moscow first, Moscow second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(Moscow first, Moscow second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(Moscow first, Moscow second)
        {
            return first.Population != second.Population;
        }
    }
}
