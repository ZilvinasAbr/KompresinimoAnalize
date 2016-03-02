#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Helpers.h"
#include <map>
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
	static bool ReadK(ifstream & inputFileStream, unsigned & k);
	static void OutputK(ofstream & outputFileStream, map<unsigned, vector<BYTE>>& dictionary, unsigned k);
	static void OutputByteVector(ofstream &outputFileStream, vector<BYTE> &byteVector);
	static void AddNewEntry(map< unsigned, vector<BYTE> > &dictionary, BYTE &newByte, vector<BYTE> w, unsigned &index);
	
};

