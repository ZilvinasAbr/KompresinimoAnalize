#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LempelZivAlgorithm/Helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LZWAlgorithmUnitTests
{
	TEST_CLASS(CharToByteUnitTest)
	{
	public:

		TEST_METHOD(CharToByteTest1)
		{
			Assert::AreEqual(CharToByte(-128), BYTE(128), L"message");
		}
		TEST_METHOD(CharToByteTest2)
		{
			// TODO: Your test code here
			Assert::AreEqual(CharToByte(-1), BYTE(255), L"message");
		}
		TEST_METHOD(CharToByteTest3)
		{
			// TODO: Your test code here
			Assert::AreEqual(CharToByte(-127), BYTE(129), L"message");
		}

	};
}