using System;
using System.Collections.Generic;
using LZWAlgorithm;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTests
{
    [TestClass]
    public class ByteArrayComparerTests
    {
        [TestMethod]
        public void DoesHashFunctionWork()
        {
            var dict = new Dictionary<byte[], string>(new ByteArrayComparer());
            byte[] test1 = { 10, 20, 12, 1, 5, 8, 4 };
            byte[] test2 = { 10, 20, 12, 1, 5, 8, 4 };

            dict.Add(test1, "Labas1");

            Assert.AreEqual(true, dict.ContainsKey(test2));
        }
    }
}
