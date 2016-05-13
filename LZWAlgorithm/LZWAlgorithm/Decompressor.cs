using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LZWAlgorithm
{
    class Decompressor
    {
        /// <summary>
        /// ByteGetter yra sukurta klase, kuri reikalinga tam, kad butu
        /// patogiau nuskaitomi List byte pagal encodedData 
        /// </summary>
        /// <param name="inputFileName"></param>
        /// <param name="outputFileName"></param>
        public static void Decompress(string inputFileName, string outputFileName)
        {
            List<byte> decodedData = new List<byte>();
            byte[] encodedDataArray = File.ReadAllBytes(inputFileName);
            List<List<byte>> dictionary = InitializeDictionary();
            ByteGetter bg = new ByteGetter(encodedDataArray.ToList(), dictionary);

            List<byte> w = bg.NextByteList();

            while (!bg.IsEmpty())
            {
                var output = bg.NextByteList();
                decodedData.AddRange(output);//adds output to decodedData
                w.Add(output[0]); //adds first byte from output to w, which is then added to dictionary
                dictionary.Add(w);//adds new entry
                w.RemoveAt(w.Count - 1); //removes last element to leave only the conjecture
            }

            File.WriteAllBytes(outputFileName, decodedData.ToArray());

        }

        public static List<List<byte>> InitializeDictionary()
        {
            List<List<byte>> result = new List<List<byte>>();

            for (int i = 0; i < 256; i++)
            {
                List<byte> temp = new List<byte> {(byte) i};
                result.Add(temp);
            }

            return result;
        }
    }
}
