using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PropertiesInAbstractClass
{
    abstract class Product
    {
        private static int serial = 0;
        public string SerialID
        {
            get { return String.Format("{0:d5}", serial++); }
        }
        abstract public DateTime ProductDate
        {
            get;set;
        }
    }
    
    class MyProduct : Product
    {
        public override DateTime ProductDate
        {
            get;set;
        }
    }
    internal class PropertiesInAbstractClass
    {
    }
}
