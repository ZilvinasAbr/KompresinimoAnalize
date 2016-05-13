using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LZWAlgorithm
{
    public class DynamicBitArray
    {
        private readonly List<byte> _data;
        private readonly List<bool> _buffer;

        public DynamicBitArray()
        {
            _data = new List<byte>();
            _buffer = new List<bool>();
        }

        /// <summary>
        /// This method also adds buffer's bits to the result
        /// </summary>
        /// <returns></returns>
        public List<byte> GetData()
        {
            if (_buffer.Count != 0)
            {
                while (_buffer.Count != 8)
                    _buffer.Add(false);
            }

            WriteBuffer();

            return _data;
        }

        public void Add(bool value)
        {
            _buffer.Add(value);
            if (_buffer.Count == 8)
            {
                WriteBuffer();
            }
        }

        private void WriteBuffer()
        {
            byte result = BoolArrayToByte(_buffer);
            _data.Add(result);
            _buffer.Clear();
        }

        private byte BoolArrayToByte(IEnumerable<bool> arr)
        {
            byte val = 0;
            foreach (bool b in arr)
            {
                val <<= 1;
                if (b) val |= 1;
            }
            return val;
        }
    }
}
