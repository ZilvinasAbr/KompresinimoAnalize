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
        public void GetLengthTest()
        {
            Helpers dh = new Helpers();

            Assert.AreEqual(dh.GetLength(32), 6);
        }
    }
}