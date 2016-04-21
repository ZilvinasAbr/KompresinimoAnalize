#pragma once
#include <string>
#include <vector>

typedef unsigned char BYTE;
using namespace std;
class Decompressor
{
public:
	Decompressor();
	~Decompressor();
	static void Decompress(vector<bool> &encodedData, vector<char> &decodedData);
	
private:

};

