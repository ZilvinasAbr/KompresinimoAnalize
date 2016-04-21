#pragma once
#include <vector>
using namespace std;

inline vector< vector<char> > InitializeDictionary()
{
	vector< vector<char> > result;
	char counter = -128;
	for(int i=0;i<256;i++)
	{
		vector<char> temp;
		temp.push_back(counter++);
		result.push_back(temp);
	}

	return result;
}

inline vector<char> Read(vector<bool> &encodedData, int &position, vector< vector<char> > &dictionary, int decimalCounter)
{
	vector<bool> bits;
	int number = 32;

	int lengthOfCode = 5;

	while (decimalCounter >= number)
	{
		lengthOfCode++;
		number = number << 1;
	}

	bits.insert(bits.end(), encodedData.begin() + position, encodedData.begin() + position + lengthOfCode);

	int code = 0;
	int num = 1;
	for(int i=bits.size()-1;i>=0;i--)
	{
		if (bits[i])
			code += num;
		num = num << 1;
	}
	position += lengthOfCode;

	return dictionary[code];
}