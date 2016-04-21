#pragma once
#include <string>
#include <vector>
using namespace std;

class Compressor
{
public:
	Compressor();
	~Compressor();
	static void Compress(vector<char> &originalData, vector<bool> &encodedData);
private:

};

