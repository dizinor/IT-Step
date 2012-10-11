using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Germany
{
    class Berlin
    {
        public int Population { get; set; }
        public Berlin():this(4096){}
        public Berlin(int Population)
        {
            this.Population = Population;
        }
        static public bool operator > (Berlin first, Berlin second)
        {                                    
            return first.Population > second.Population;
        }          
        static public bool operator < (Berlin first, Berlin second)
        {          
            return first.Population < second.Population;
        }          
        static public bool operator >=(Berlin first, Berlin second)
        {          
            return first.Population >= second.Population;
        }          
        static public bool operator <=(Berlin first, Berlin second)
        {          
            return first.Population <= second.Population;
        }          
        static public bool operator ==(Berlin first, Berlin second)
        {          
            return first.Population == second.Population;
        }          
        static public bool operator !=(Berlin first, Berlin second)
        {          
            return first.Population != second.Population;
        }
        static public bool operator > (Berlin first, GreatBritain.London second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (Berlin first, GreatBritain.London second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(Berlin first, GreatBritain.London second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(Berlin first, GreatBritain.London second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(Berlin first, GreatBritain.London second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(Berlin first, GreatBritain.London second)
        {
            return first.Population != second.Population;
        }
        static public bool operator > (Berlin first, Russia.Moscow second)
        {
            return first.Population > second.Population;
        }
        static public bool operator < (Berlin first, Russia.Moscow second)
        {
            return first.Population < second.Population;
        }
        static public bool operator >=(Berlin first, Russia.Moscow second)
        {
            return first.Population >= second.Population;
        }
        static public bool operator <=(Berlin first, Russia.Moscow second)
        {
            return first.Population <= second.Population;
        }
        static public bool operator ==(Berlin first, Russia.Moscow second)
        {
            return first.Population == second.Population;
        }
        static public bool operator !=(Berlin first, Russia.Moscow second)
        {
            return first.Population != second.Population;
        }
    }
}
