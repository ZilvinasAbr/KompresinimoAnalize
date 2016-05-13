using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LZWAlgorithm
{
    public class Helpers
    {
        private readonly List<List<bool>> _byteDictionary;

        public Helpers()
        {
            _byteDictionary = InitializeByteDictionary();
        }
        
        public int GetIntFromBits(List<bool> bits)
        {
            int result = 0;
            for (int i = 0; i < bits.Count; i++)
            {
                if (bits[i])
                {
                    result += (int)Math.Pow(2, i);
                }
            }
            return result;
        }

        public List<bool> GetBoolListFromByte(byte b)
        {
            return _byteDictionary[(int)b];
        }

        public int GetLength(int nextIndex)
        {

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

        private List<List<bool>> InitializeByteDictionary()
        {
            //I know this looks retarded, but I have no time do it differently
            #region Long dictionary
            List<List<bool>> byteDictionary = new List<List<bool>>
            {
                new List<bool> {false, false, false, false, false, false, false, false},
                new List<bool> {false, false, false, false, false, false, false, true},
                new List<bool> {false, false, false, false, false, false, true, false},
                new List<bool> {false, false, false, false, false, false, true, true},
                new List<bool> {false, false, false, false, false, true, false, false},
                new List<bool> {false, false, false, false, false, true, false, true},
                new List<bool> {false, false, false, false, false, true, true, false},
                new List<bool> {false, false, false, false, false, true, true, true},
                new List<bool> {false, false, false, false, true, false, false, false},
                new List<bool> {false, false, false, false, true, false, false, true},
                new List<bool> {false, false, false, false, true, false, true, false},
                new List<bool> {false, false, false, false, true, false, true, true},
                new List<bool> {false, false, false, false, true, true, false, false},
                new List<bool> {false, false, false, false, true, true, false, true},
                new List<bool> {false, false, false, false, true, true, true, false},
                new List<bool> {false, false, false, false, true, true, true, true},
                new List<bool> {false, false, false, true, false, false, false, false},
                new List<bool> {false, false, false, true, false, false, false, true},
                new List<bool> {false, false, false, true, false, false, true, false},
                new List<bool> {false, false, false, true, false, false, true, true},
                new List<bool> {false, false, false, true, false, true, false, false},
                new List<bool> {false, false, false, true, false, true, false, true},
                new List<bool> {false, false, false, true, false, true, true, false},
                new List<bool> {false, false, false, true, false, true, true, true},
                new List<bool> {false, false, false, true, true, false, false, false},
                new List<bool> {false, false, false, true, true, false, false, true},
                new List<bool> {false, false, false, true, true, false, true, false},
                new List<bool> {false, false, false, true, true, false, true, true},
                new List<bool> {false, false, false, true, true, true, false, false},
                new List<bool> {false, false, false, true, true, true, false, true},
                new List<bool> {false, false, false, true, true, true, true, false},
                new List<bool> {false, false, false, true, true, true, true, true},
                new List<bool> {false, false, true, false, false, false, false, false},
                new List<bool> {false, false, true, false, false, false, false, true},
                new List<bool> {false, false, true, false, false, false, true, false},
                new List<bool> {false, false, true, false, false, false, true, true},
                new List<bool> {false, false, true, false, false, true, false, false},
                new List<bool> {false, false, true, false, false, true, false, true},
                new List<bool> {false, false, true, false, false, true, true, false},
                new List<bool> {false, false, true, false, false, true, true, true},
                new List<bool> {false, false, true, false, true, false, false, false},
                new List<bool> {false, false, true, false, true, false, false, true},
                new List<bool> {false, false, true, false, true, false, true, false},
                new List<bool> {false, false, true, false, true, false, true, true},
                new List<bool> {false, false, true, false, true, true, false, false},
                new List<bool> {false, false, true, false, true, true, false, true},
                new List<bool> {false, false, true, false, true, true, true, false},
                new List<bool> {false, false, true, false, true, true, true, true},
                new List<bool> {false, false, true, true, false, false, false, false},
                new List<bool> {false, false, true, true, false, false, false, true},
                new List<bool> {false, false, true, true, false, false, true, false},
                new List<bool> {false, false, true, true, false, false, true, true},
                new List<bool> {false, false, true, true, false, true, false, false},
                new List<bool> {false, false, true, true, false, true, false, true},
                new List<bool> {false, false, true, true, false, true, true, false},
                new List<bool> {false, false, true, true, false, true, true, true},
                new List<bool> {false, false, true, true, true, false, false, false},
                new List<bool> {false, false, true, true, true, false, false, true},
                new List<bool> {false, false, true, true, true, false, true, false},
                new List<bool> {false, false, true, true, true, false, true, true},
                new List<bool> {false, false, true, true, true, true, false, false},
                new List<bool> {false, false, true, true, true, true, false, true},
                new List<bool> {false, false, true, true, true, true, true, false},
                new List<bool> {false, false, true, true, true, true, true, true},
                new List<bool> {false, true, false, false, false, false, false, false},
                new List<bool> {false, true, false, false, false, false, false, true},
                new List<bool> {false, true, false, false, false, false, true, false},
                new List<bool> {false, true, false, false, false, false, true, true},
                new List<bool> {false, true, false, false, false, true, false, false},
                new List<bool> {false, true, false, false, false, true, false, true},
                new List<bool> {false, true, false, false, false, true, true, false},
                new List<bool> {false, true, false, false, false, true, true, true},
                new List<bool> {false, true, false, false, true, false, false, false},
                new List<bool> {false, true, false, false, true, false, false, true},
                new List<bool> {false, true, false, false, true, false, true, false},
                new List<bool> {false, true, false, false, true, false, true, true},
                new List<bool> {false, true, false, false, true, true, false, false},
                new List<bool> {false, true, false, false, true, true, false, true},
                new List<bool> {false, true, false, false, true, true, true, false},
                new List<bool> {false, true, false, false, true, true, true, true},
                new List<bool> {false, true, false, true, false, false, false, false},
                new List<bool> {false, true, false, true, false, false, false, true},
                new List<bool> {false, true, false, true, false, false, true, false},
                new List<bool> {false, true, false, true, false, false, true, true},
                new List<bool> {false, true, false, true, false, true, false, false},
                new List<bool> {false, true, false, true, false, true, false, true},
                new List<bool> {false, true, false, true, false, true, true, false},
                new List<bool> {false, true, false, true, false, true, true, true},
                new List<bool> {false, true, false, true, true, false, false, false},
                new List<bool> {false, true, false, true, true, false, false, true},
                new List<bool> {false, true, false, true, true, false, true, false},
                new List<bool> {false, true, false, true, true, false, true, true},
                new List<bool> {false, true, false, true, true, true, false, false},
                new List<bool> {false, true, false, true, true, true, false, true},
                new List<bool> {false, true, false, true, true, true, true, false},
                new List<bool> {false, true, false, true, true, true, true, true},
                new List<bool> {false, true, true, false, false, false, false, false},
                new List<bool> {false, true, true, false, false, false, false, true},
                new List<bool> {false, true, true, false, false, false, true, false},
                new List<bool> {false, true, true, false, false, false, true, true},
                new List<bool> {false, true, true, false, false, true, false, false},
                new List<bool> {false, true, true, false, false, true, false, true},
                new List<bool> {false, true, true, false, false, true, true, false},
                new List<bool> {false, true, true, false, false, true, true, true},
                new List<bool> {false, true, true, false, true, false, false, false},
                new List<bool> {false, true, true, false, true, false, false, true},
                new List<bool> {false, true, true, false, true, false, true, false},
                new List<bool> {false, true, true, false, true, false, true, true},
                new List<bool> {false, true, true, false, true, true, false, false},
                new List<bool> {false, true, true, false, true, true, false, true},
                new List<bool> {false, true, true, false, true, true, true, false},
                new List<bool> {false, true, true, false, true, true, true, true},
                new List<bool> {false, true, true, true, false, false, false, false},
                new List<bool> {false, true, true, true, false, false, false, true},
                new List<bool> {false, true, true, true, false, false, true, false},
                new List<bool> {false, true, true, true, false, false, true, true},
                new List<bool> {false, true, true, true, false, true, false, false},
                new List<bool> {false, true, true, true, false, true, false, true},
                new List<bool> {false, true, true, true, false, true, true, false},
                new List<bool> {false, true, true, true, false, true, true, true},
                new List<bool> {false, true, true, true, true, false, false, false},
                new List<bool> {false, true, true, true, true, false, false, true},
                new List<bool> {false, true, true, true, true, false, true, false},
                new List<bool> {false, true, true, true, true, false, true, true},
                new List<bool> {false, true, true, true, true, true, false, false},
                new List<bool> {false, true, true, true, true, true, false, true},
                new List<bool> {false, true, true, true, true, true, true, false},
                new List<bool> {false, true, true, true, true, true, true, true},
                new List<bool> {true, false, false, false, false, false, false, false},
                new List<bool> {true, false, false, false, false, false, false, true},
                new List<bool> {true, false, false, false, false, false, true, false},
                new List<bool> {true, false, false, false, false, false, true, true},
                new List<bool> {true, false, false, false, false, true, false, false},
                new List<bool> {true, false, false, false, false, true, false, true},
                new List<bool> {true, false, false, false, false, true, true, false},
                new List<bool> {true, false, false, false, false, true, true, true},
                new List<bool> {true, false, false, false, true, false, false, false},
                new List<bool> {true, false, false, false, true, false, false, true},
                new List<bool> {true, false, false, false, true, false, true, false},
                new List<bool> {true, false, false, false, true, false, true, true},
                new List<bool> {true, false, false, false, true, true, false, false},
                new List<bool> {true, false, false, false, true, true, false, true},
                new List<bool> {true, false, false, false, true, true, true, false},
                new List<bool> {true, false, false, false, true, true, true, true},
                new List<bool> {true, false, false, true, false, false, false, false},
                new List<bool> {true, false, false, true, false, false, false, true},
                new List<bool> {true, false, false, true, false, false, true, false},
                new List<bool> {true, false, false, true, false, false, true, true},
                new List<bool> {true, false, false, true, false, true, false, false},
                new List<bool> {true, false, false, true, false, true, false, true},
                new List<bool> {true, false, false, true, false, true, true, false},
                new List<bool> {true, false, false, true, false, true, true, true},
                new List<bool> {true, false, false, true, true, false, false, false},
                new List<bool> {true, false, false, true, true, false, false, true},
                new List<bool> {true, false, false, true, true, false, true, false},
                new List<bool> {true, false, false, true, true, false, true, true},
                new List<bool> {true, false, false, true, true, true, false, false},
                new List<bool> {true, false, false, true, true, true, false, true},
                new List<bool> {true, false, false, true, true, true, true, false},
                new List<bool> {true, false, false, true, true, true, true, true},
                new List<bool> {true, false, true, false, false, false, false, false},
                new List<bool> {true, false, true, false, false, false, false, true},
                new List<bool> {true, false, true, false, false, false, true, false},
                new List<bool> {true, false, true, false, false, false, true, true},
                new List<bool> {true, false, true, false, false, true, false, false},
                new List<bool> {true, false, true, false, false, true, false, true},
                new List<bool> {true, false, true, false, false, true, true, false},
                new List<bool> {true, false, true, false, false, true, true, true},
                new List<bool> {true, false, true, false, true, false, false, false},
                new List<bool> {true, false, true, false, true, false, false, true},
                new List<bool> {true, false, true, false, true, false, true, false},
                new List<bool> {true, false, true, false, true, false, true, true},
                new List<bool> {true, false, true, false, true, true, false, false},
                new List<bool> {true, false, true, false, true, true, false, true},
                new List<bool> {true, false, true, false, true, true, true, false},
                new List<bool> {true, false, true, false, true, true, true, true},
                new List<bool> {true, false, true, true, false, false, false, false},
                new List<bool> {true, false, true, true, false, false, false, true},
                new List<bool> {true, false, true, true, false, false, true, false},
                new List<bool> {true, false, true, true, false, false, true, true},
                new List<bool> {true, false, true, true, false, true, false, false},
                new List<bool> {true, false, true, true, false, true, false, true},
                new List<bool> {true, false, true, true, false, true, true, false},
                new List<bool> {true, false, true, true, false, true, true, true},
                new List<bool> {true, false, true, true, true, false, false, false},
                new List<bool> {true, false, true, true, true, false, false, true},
                new List<bool> {true, false, true, true, true, false, true, false},
                new List<bool> {true, false, true, true, true, false, true, true},
                new List<bool> {true, false, true, true, true, true, false, false},
                new List<bool> {true, false, true, true, true, true, false, true},
                new List<bool> {true, false, true, true, true, true, true, false},
                new List<bool> {true, false, true, true, true, true, true, true},
                new List<bool> {true, true, false, false, false, false, false, false},
                new List<bool> {true, true, false, false, false, false, false, true},
                new List<bool> {true, true, false, false, false, false, true, false},
                new List<bool> {true, true, false, false, false, false, true, true},
                new List<bool> {true, true, false, false, false, true, false, false},
                new List<bool> {true, true, false, false, false, true, false, true},
                new List<bool> {true, true, false, false, false, true, true, false},
                new List<bool> {true, true, false, false, false, true, true, true},
                new List<bool> {true, true, false, false, true, false, false, false},
                new List<bool> {true, true, false, false, true, false, false, true},
                new List<bool> {true, true, false, false, true, false, true, false},
                new List<bool> {true, true, false, false, true, false, true, true},
                new List<bool> {true, true, false, false, true, true, false, false},
                new List<bool> {true, true, false, false, true, true, false, true},
                new List<bool> {true, true, false, false, true, true, true, false},
                new List<bool> {true, true, false, false, true, true, true, true},
                new List<bool> {true, true, false, true, false, false, false, false},
                new List<bool> {true, true, false, true, false, false, false, true},
                new List<bool> {true, true, false, true, false, false, true, false},
                new List<bool> {true, true, false, true, false, false, true, true},
                new List<bool> {true, true, false, true, false, true, false, false},
                new List<bool> {true, true, false, true, false, true, false, true},
                new List<bool> {true, true, false, true, false, true, true, false},
                new List<bool> {true, true, false, true, false, true, true, true},
                new List<bool> {true, true, false, true, true, false, false, false},
                new List<bool> {true, true, false, true, true, false, false, true},
                new List<bool> {true, true, false, true, true, false, true, false},
                new List<bool> {true, true, false, true, true, false, true, true},
                new List<bool> {true, true, false, true, true, true, false, false},
                new List<bool> {true, true, false, true, true, true, false, true},
                new List<bool> {true, true, false, true, true, true, true, false},
                new List<bool> {true, true, false, true, true, true, true, true},
                new List<bool> {true, true, true, false, false, false, false, false},
                new List<bool> {true, true, true, false, false, false, false, true},
                new List<bool> {true, true, true, false, false, false, true, false},
                new List<bool> {true, true, true, false, false, false, true, true},
                new List<bool> {true, true, true, false, false, true, false, false},
                new List<bool> {true, true, true, false, false, true, false, true},
                new List<bool> {true, true, true, false, false, true, true, false},
                new List<bool> {true, true, true, false, false, true, true, true},
                new List<bool> {true, true, true, false, true, false, false, false},
                new List<bool> {true, true, true, false, true, false, false, true},
                new List<bool> {true, true, true, false, true, false, true, false},
                new List<bool> {true, true, true, false, true, false, true, true},
                new List<bool> {true, true, true, false, true, true, false, false},
                new List<bool> {true, true, true, false, true, true, false, true},
                new List<bool> {true, true, true, false, true, true, true, false},
                new List<bool> {true, true, true, false, true, true, true, true},
                new List<bool> {true, true, true, true, false, false, false, false},
                new List<bool> {true, true, true, true, false, false, false, true},
                new List<bool> {true, true, true, true, false, false, true, false},
                new List<bool> {true, true, true, true, false, false, true, true},
                new List<bool> {true, true, true, true, false, true, false, false},
                new List<bool> {true, true, true, true, false, true, false, true},
                new List<bool> {true, true, true, true, false, true, true, false},
                new List<bool> {true, true, true, true, false, true, true, true},
                new List<bool> {true, true, true, true, true, false, false, false},
                new List<bool> {true, true, true, true, true, false, false, true},
                new List<bool> {true, true, true, true, true, false, true, false},
                new List<bool> {true, true, true, true, true, false, true, true},
                new List<bool> {true, true, true, true, true, true, false, false},
                new List<bool> {true, true, true, true, true, true, false, true},
                new List<bool> {true, true, true, true, true, true, true, false},
                new List<bool> {true, true, true, true, true, true, true, true}
            };
            #endregion

            return byteDictionary;
        }
    }
}
