#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LempelZivAlgorithm/Helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LZWAlgorithmUnitTests
{		
	TEST_CLASS(ByteToCharUnitTest)
	{
	public:
		
		TEST_METHOD(ByteToCharTest1)
		{
			// TODO: Your test code here
			Assert::AreEqual(ByteToChar(255), char(-1), L"message");
		}
		TEST_METHOD(ByteToCharTest2)
		{
			// TODO: Your test code here
			Assert::AreEqual(ByteToChar(128), char(-128), L"message");
		}
		TEST_METHOD(ByteToCharTest3)
		{
			// TODO: Your test code here
			Assert::AreEqual(ByteToChar(129), char(-127), L"message");
		}

	};
}