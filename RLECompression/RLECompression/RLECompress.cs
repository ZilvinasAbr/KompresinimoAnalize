using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HuffmanCompression
{
    static class RLECompress
    {
        public static byte[] Compress(byte[] originalData)
        {
            List<byte> compressedData = new List<byte>();
            byte counter = 0;
            byte lastByte = originalData[0];
            bool first = true;
            foreach (byte b in originalData)
            {
                if (first)
                {
                    counter++;
                    first = false;
                    continue;
                }
                if (lastByte != b || counter == 255)
                {
                    if (counter == 1)
                    {
                        compressedData.Add(lastByte);
                    }
                    else
                    {
                        compressedData.Add(lastByte);
                        compressedData.Add(lastByte);
                        counter--;
                        counter--;
                        compressedData.Add(counter);
                    }
                    counter = 0;
                }
                counter++;
                lastByte = b;
            }
            if (counter > 1)
            {
                compressedData.Add(lastByte);
                compressedData.Add(lastByte);
                counter--;
                counter--;
                compressedData.Add(counter);
            }
            else
            {
                compressedData.Add(lastByte);
            }
            return compressedData.ToArray();
        }
    }
}
