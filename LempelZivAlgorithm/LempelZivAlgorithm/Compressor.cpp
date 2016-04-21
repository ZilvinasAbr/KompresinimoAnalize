#include "Compressor.h"
#include <vector>
#include "CompressorHelpers.h"
using namespace std;


Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

void Compressor::Compress(vector<char> &originalData, vector<bool> &encodedData)
{
	//vector<char> originalData = { 'T', 'O', 'B', 'E', 'O', 'R', 'N', 'O', 'T', 'T', 'O', 'B', 'E', 'O', 'R', 'T', 'O', 'B', 'E', 'O', 'R', 'N', 'O', 'T' };
	//vector<bool> encodedData;
	map< vector<char>, int> dictionary = InitializeDictionary();
	vector<char> w;
	int decimalCounter = 256;

	for(char &c : originalData)
	{
		w.push_back(c);

		if(dictionary.find(w) == dictionary.end())
		{
			w.pop_back();
			WriteCode(encodedData, dictionary.find(w)->second, decimalCounter);
			w.push_back(c);
			dictionary.insert(pair< vector<char>, int>(w, decimalCounter++));
			w.clear();
			w.push_back(c);
		}
	}
	WriteCode(encodedData, dictionary.find(w)->second, decimalCounter);
}
