#pragma once
#include <string>
#include <fstream>
#include "MinimalNode.h"
using namespace std;
typedef unsigned char BYTE;

class Decompressor
{
public:
	Decompressor();
	~Decompressor();
	static void Decompress(string inputFile, string outputFile);
};

