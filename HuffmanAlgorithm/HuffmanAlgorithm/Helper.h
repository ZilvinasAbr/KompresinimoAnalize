#pragma once
#include <string>
#include <vector>
using namespace std;

inline void InsertBools(std::string code, std::list<bool> &booleans)
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