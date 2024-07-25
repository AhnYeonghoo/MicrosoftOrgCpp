using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReadonlyStructure
{
    readonly struct RGBColor
    {
        public readonly byte R, G, B;
        public RGBColor(byte r, byte g, byte b)
        {
            R = r;
            G = g;
            B = b;
        }
    }
    internal class ReadonlyStructure
    {
    }
}
