using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LZWAlgorithm
{
    class Program
    {
        static void Main(string[] args)
        {
            string inputFileName = "text.txt";
            string compressedFileName = inputFileName + ".lzw";
            string decompressedFileName = "decompressed" + inputFileName;

            Compressor.Compress(inputFileName, compressedFileName);
            Decompressor.Decompress(compressedFileName, decompressedFileName);
        }
    }
}
