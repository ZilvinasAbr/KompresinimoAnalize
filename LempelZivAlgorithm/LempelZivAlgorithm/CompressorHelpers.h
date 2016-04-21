#pragma once
#include <map>
#include <stack>
#include <vector>
using namespace std;

inline map< vector<char>, int> InitializeDictionary()
{
	map< vector<char>, int> result;
	int counter = 0;

	for(int i = -128;i<=127;i++)
	{
		vector<char> temp; temp.push_back(char(i));
		result.insert(pair<vector<char>, int>(temp, counter++));
	}

	return result;
}

inline void WriteCode(vector<bool> &encodedData, int code, int decimalCounter)
{
	int lengthOfCode = 5;

	int number = 32;
	while (decimalCounter > number)
	{
		lengthOfCode++;
		number = number << 1;
	}

	stack<bool> stack;
	for(int i=0;i<lengthOfCode;i++)
	{
		int result = code % 2;
		stack.push(result);
		code = code >> 1;
	}
	for(int i=0;i<lengthOfCode;i++)
	{
		encodedData.push_back(stack.top());
		stack.pop();
	}
}