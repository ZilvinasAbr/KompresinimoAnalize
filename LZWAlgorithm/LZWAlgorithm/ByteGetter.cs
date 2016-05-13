using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;

namespace LZWAlgorithm
{
    public class ByteGetter
    {
        private readonly List<byte> _data;
        private readonly List<List<byte>> _dictionary;
        private readonly List<bool> _buffer;
        private readonly Helpers _decompressorHelpers;

        public ByteGetter(List<byte> data, List<List<byte>> dictionary )
        {
            _data = data;
            _dictionary = dictionary;
            _buffer = new List<bool>();
            _decompressorHelpers = new Helpers();
        }

        public bool IsEmpty()
        {
            if (_data.Count == 0 && _buffer.Count == 0)
                return true;
            return false;
        }

        public List<byte> NextByteList()
        {
            //Get Bits
            int lengthToRead = GetLength();

            while (_buffer.Count < lengthToRead)
            {
                byte byteTaken = _data[0];
                _data.RemoveAt(0);
                _buffer.AddRange(_decompressorHelpers.GetBoolListFromByte(byteTaken));
            }

            var bits = _buffer.GetRange(0, lengthToRead); //read from buffers first element
            _buffer.RemoveRange(0, lengthToRead); //remove read elements

            //From Bits get Code
            var code = _decompressorHelpers.GetIntFromBits(bits);

            //From Code get OutputSequence
            var outputSequence = _dictionary[code];

            //Return OutputSequence
            return outputSequence;
        }

        private int GetLength()
        {
            int nextIndex = _dictionary.Count;

            //Dont judge me for this
            #region Dont judge me for this
            if (nextIndex < 32)
            {
                return 5;
            }
            if (nextIndex < 64)
            {
                return 6;
            }
            if (nextIndex < 128)
            {
                return 7;
            }
            if (nextIndex < 256)
            {
                return 8;
            }
            if (nextIndex < 512)
            {
                return 9;
            }
            if (nextIndex < 1024)
            {
                return 10;
            }
            if (nextIndex < 2048)
            {
                return 11;
            }
            if (nextIndex < 4096)
            {
                return 12;
            }
            if (nextIndex < 4096 * 2)
            {
                return 13;
            }
            if (nextIndex < 4096 * 4)
            {
                return 14;
            }
            if (nextIndex < 4096 * 8)
            {
                return 15;
            }
            if (nextIndex < 4096 * 16)
            {
                return 16;
            }
            if (nextIndex < 4096 * 32)
            {
                return 17;
            }
            if (nextIndex < 4096 * 64)
            {
                return 18;
            }
            if (nextIndex < 4096 * 128)
            {
                return 19;
            }
            if (nextIndex < 4096 * 256)
            {
                return 20;
            }
            if (nextIndex < 4096 * 512)
            {
                return 21;
            }
            if (nextIndex < 4096 * 1024)
            {
                return 22;
            }
            if (nextIndex < 4096 * 2048)
            {
                return 23;
            }
            if (nextIndex < 4096 * 4096)
            {
                return 24;
            }
            if (nextIndex < 4096 * 4096 * 2)
            {
                return 25;
            }
            if (nextIndex < 4096 * 4096 * 4)
            {
                return 26;
            }
            if (nextIndex < 4096 * 4096 * 8)
            {
                return 27;
            }
            if (nextIndex < 4096 * 4096 * 16)
            {
                return 28;
            }
            if (nextIndex < 4096 * 4096 * 32)
            {
                return 29;
            }
            if (nextIndex < 4096 * 4096 * 64)
            {
                return 30;
            }

            return 31;
            #endregion

        }
    }
}
