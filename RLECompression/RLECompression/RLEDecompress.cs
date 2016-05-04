using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HuffmanCompression
{
    static class RLEDecompress
    {
        public static byte[] Decompress(byte[] compressedData)
        {
            List<byte> originalData = new List<byte>();
            bool counter = false;
            bool first = true;
            bool last = false;
            byte lastByte = new byte();
            foreach (byte b in compressedData)
            {
                if (first)
                {
                    lastByte = b;
                    first = false;
                    continue;
                }
                if (counter)
                {
                    byte size = b;
                    size++;
                    size++;
                    for (int i = 0; i < size; i++)
                    {
                        originalData.Add(lastByte);
                    }
                    counter = false;
                    last = false;
                    first = true;
                    continue;
                }
                if (lastByte == b)
                {
                    counter = true;
                }
                else
                {
                    originalData.Add(lastByte);
                    last = true;
                }
                lastByte = b;
            }
            if (last)
            {
                originalData.Add(lastByte);
            }
            return originalData.ToArray();
        }
    }
}
