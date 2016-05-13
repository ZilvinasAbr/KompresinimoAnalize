using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LZWAlgorithm
{
    class Compressor
    {
        public static void Compress(string inputFileName, string outputFileName)
        {
            DynamicBitArray compressedData = new DynamicBitArray();

            Dictionary<byte[], int> dictionary = InitializeDictionary();
            List<byte> w = new List<byte>();
            int decimalCounter = 256;
            byte[] inputFileData = File.ReadAllBytes(inputFileName);

            foreach (var b in inputFileData)
            {
                w.Add(b);

                if (!dictionary.ContainsKey(w.ToArray()))
                {
                    w.RemoveAt(w.Count - 1);
                    int code = dictionary[w.ToArray()];
                    WriteCode(compressedData, code, decimalCounter);
                    w.Add(b);
                    dictionary.Add(w.ToArray(), decimalCounter++);
                    w.Clear();
                    w.Add(b);
                }
            }
            WriteCode(compressedData, dictionary[w.ToArray()], decimalCounter);
            File.WriteAllBytes(outputFileName, compressedData.GetData().ToArray());
        }

        public static Dictionary<byte[], int> InitializeDictionary()
        {
            Dictionary<byte[], int> result = new Dictionary<byte[], int>(new ByteArrayComparer());
            List<byte> temp = new List<byte>();

            for (int i = 0; i < 256; i++)
            {
                temp.Add((byte) i);
                result.Add(temp.ToArray(), i);
                temp.Clear();
            }

            return result;
        }

        public static void WriteCode(DynamicBitArray compressedData, int code, int decimalCounter)
        {
            int lengthOfCode = 5;

            int number = 32;

            while (decimalCounter > number)
            {
                lengthOfCode++;
                number = number << 1;
            }

            Stack<bool> stack = new Stack<bool>();
            for (int i = 0; i < lengthOfCode; i++)
            {
                bool result = code%2 == 1 ? true : false;
                stack.Push(result);
                code >>= 1;
            }

            for (int i = 0; i < lengthOfCode; i++)
            {
                compressedData.Add(stack.Pop());
            }
        }
    }
}
