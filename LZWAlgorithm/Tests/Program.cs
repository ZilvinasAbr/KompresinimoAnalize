using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LZWAlgorithm;

namespace Tests
{
    class Program
    {
        static void Main(string[] args)
        {
            var dict = new Dictionary<byte[], string>(new ByteArrayComparer());
            byte[] test1 = { 10, 20, 12, 1, 5, 8, 4 };
            byte[] test2 = { 10, 20, 12, 1, 5, 8, 4 };

            dict.Add(test1, "Labas1");
            dict.Add(test2, "Labas2");

            foreach (var a in dict)
            {
                System.Console.WriteLine("Raktas {0}\nReiksme {1}", a.Key, a.Value);
            } 
        }
    }
}
