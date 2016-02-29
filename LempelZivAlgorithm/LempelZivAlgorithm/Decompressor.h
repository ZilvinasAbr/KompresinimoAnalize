#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Helpers.h"
typedef unsigned char BYTE;
using namespace std;
class Decompressor
{
public:
	Decompressor();
	~Decompressor();
	static void Decompress(string inputFile, string outputFile);
private:
	static void InitializeDictionary(map< unsigned, vector<BYTE> > &dictionary);
};

