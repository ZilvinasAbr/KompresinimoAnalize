#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Helpers.h"
#include <map>
typedef unsigned char BYTE;
using namespace std;

class Compressor
{
public:
	Compressor();
	~Compressor();
	static void Compress(std::string inputFile, std::string outputFile);
private:
	static void InitializeDictionary(map< vector<BYTE>, unsigned> &dictionary);
	static bool WkExistsInDictionary(map< vector<BYTE>, unsigned> &dictionary, vector<BYTE> &wk);
	static void AddWkToDictionary(map<vector<BYTE>, unsigned>& dictionary, vector<BYTE>& wk, int index);
	static void OutputW(map<vector<BYTE>, unsigned>& dictionary, vector<BYTE>& w, unsigned & index, vector<char> & outputBuffer);
};

