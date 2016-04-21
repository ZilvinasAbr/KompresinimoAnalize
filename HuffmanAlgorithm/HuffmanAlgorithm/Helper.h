#pragma once
#include <string>
#include <vector>
using namespace std;

inline void InsertBools(string code, vector<bool> &booleans)
{
	for(char &c : code)
		booleans.push_back(c == '1' ? true : false);
}

inline vector< vector<bool> > LetterStringToBoolMapper(vector<string> &letterStringMap)
{
	vector< vector<bool> > letterBooleansMap;
	for(string &s : letterStringMap)
	{
		vector<bool> result;
		for (char &c : s)
			result.push_back(c == '1' ? true : false);
		letterBooleansMap.push_back(result);
	}
	return letterBooleansMap;
}

inline char VectorBoolsToChar(vector<bool> bools)
{
	char c = 0;
	for (int i = 0; i < 8; i++)
		c += (bools[i] << i); // 0 or 1 times 2 to the ith power

	return c;
}