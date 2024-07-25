using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProperiesInheritance
{
    interface INamedValue
    {
        string Name
        {
            get;
            set;

        }

        string Value
        {
            get;
            set;
        }
    }

    class NamedValue : INamedValue
    {
        public string Name { get; set; }
        public string Value { get; set; }

    }
    internal class PropertiesInInterface
    {
    }
}
