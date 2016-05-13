using Microsoft.VisualStudio.TestTools.UnitTesting;
using LZWAlgorithm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LZWAlgorithm.Tests
{
    [TestClass()]
    public class DecompressorHelpersTests
    {
        [TestMethod()]
        public void GetIntFromBitsTest()
        {
            Helpers dh = new Helpers();
            List<bool> list = new List<bool>() {false, false, true};

            Assert.AreEqual(4, dh.GetIntFromBits(list));

            list = new List<bool>() { true, true, true, true, true, true, true };
            Assert.AreEqual(127, dh.GetIntFromBits(list));
        }
    }
}