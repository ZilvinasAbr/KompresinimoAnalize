#include "Compressor.h"



Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

/*
w = NIL;
while ( read a character k )
{
if wk exists in the dictionary
w = wk;
else
add wk to the dictionary;
output the code for w;
w = k;
}
*/
void Compressor::Compress(string inputFile, string outputFile)
{
	#pragma region Initialize
		unsigned index = 256;
		ifstream inputFileStream(inputFile.c_str(), ios::in | ios::binary);
		ofstream outputFileStream(outputFile.c_str(), ios::out | ios::binary);
		map< vector<BYTE>, unsigned> dictionary;
		InitializeDictionary(dictionary);
		char buffer[1];
		BYTE byteBuffer;
		vector<BYTE> w;
#pragma endregion
	while (inputFileStream.read(buffer, 1)) {
		vector<BYTE> wk = w; wk.push_back(CharToByte(buffer[0])); // wk = w+k
		if (WkExistsInDictionary(dictionary,wk)) {
			w = wk;
		}
		else {
			AddWkToDictionary(dictionary, wk, index);
			OutputW(dictionary, w, index, outputFileStream);
			w.clear(); w.push_back(byteBuffer); //w=k
		}
	}
	OutputW(dictionary, w, index, outputFileStream);

	inputFileStream.close();
	outputFileStream.close();
}

void Compressor::InitializeDictionary(map< vector<BYTE>, unsigned> &dictionary)
{
	for (auto i = 0; i < 256; i++) {
		vector<BYTE> a;
		a.push_back(i);
		dictionary.insert(pair<vector<BYTE>, unsigned>(a, i));
	}
}

bool Compressor::WkExistsInDictionary(map< vector<BYTE>, unsigned> &dictionary, vector<BYTE> &wk)
{
	std::map<vector<BYTE>, unsigned>::iterator it = dictionary.find(wk);
	if (it != dictionary.end()) {
		return true;
	}
	return false;
}

void Compressor::AddWkToDictionary(map< vector<BYTE>, unsigned> &dictionary, vector<BYTE> &wk, int index)
{
	dictionary.insert(pair<vector<BYTE>, unsigned>(wk, index));
}

void Compressor::OutputW(map< vector<BYTE>, unsigned> &dictionary, vector<BYTE> &w, unsigned &index, ofstream &outputFileStream)
{
	unsigned num = dictionary.find(w)->second;
	BYTE *byteArray = IntToByteArray(num);
	char charArray[4];
	for (int i = 0; i < 4; i++)
		charArray[i] = ByteToChar(byteArray[i]);
	outputFileStream.write(charArray, 4);
	index++;
}