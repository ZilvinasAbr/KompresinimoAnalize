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
	const int bufferLength = 1024 * 1024; // 1 MB
	unsigned index = 256;
	ifstream inputFileStream(inputFile.c_str(), ios::in | ios::binary);
	ofstream outputFileStream(outputFile.c_str(), ios::out | ios::binary);
	map< vector<BYTE>, unsigned> dictionary;
	InitializeDictionary(dictionary);
	char *buffer = new char[bufferLength];
	vector<char> outputBuffer;
	BYTE byteBuffer;
	vector<BYTE> w;
	#pragma endregion

	while(inputFileStream.read(buffer, bufferLength))
	{
		for (int i = 0; i < bufferLength;i++)
		{
			vector<BYTE> wk = w; wk.push_back(CharToByte(buffer[i])); // wk = w+k
			if (WkExistsInDictionary(dictionary, wk)) {
				w = wk;
			}
			else {
				AddWkToDictionary(dictionary, wk, index);
				OutputW(dictionary, w, index, outputBuffer);
				w.clear(); w.push_back(buffer[i]); //w=k
			}
		}
		OutputW(dictionary, w, index, outputBuffer);
		char *charArray = &outputBuffer[0];
		outputFileStream.write(charArray, outputBuffer.size());
	}
	streamsize bytesRead = inputFileStream.gcount();
	for (streamsize i = 0; i < bytesRead;i++)
	{
		vector<BYTE> wk = w; wk.push_back(CharToByte(buffer[i])); // wk = w+k
		if (WkExistsInDictionary(dictionary, wk)) {
			w = wk;
		}
		else {
			AddWkToDictionary(dictionary, wk, index);
			OutputW(dictionary, w, index, outputBuffer);
			w.clear(); w.push_back(buffer[i]); //w=k
		}
	}
	OutputW(dictionary, w, index, outputBuffer);
	char *charArray = &outputBuffer[0];
	outputFileStream.write(charArray, outputBuffer.size());





	/*while (inputFileStream.read(buffer, 1024*1024)) {
		vector<BYTE> wk = w; wk.push_back(CharToByte(buffer[0])); // wk = w+k
		if (WkExistsInDictionary(dictionary,wk)) {
			w = wk;
		}
		else {
			AddWkToDictionary(dictionary, wk, index);
			OutputW(dictionary, w, index, outputFileStream);
			w.clear(); w.push_back(buffer[0]); //w=k
		}
	}
	OutputW(dictionary, w, index, outputFileStream);*/

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

void Compressor::OutputW(map< vector<BYTE>, unsigned> &dictionary, vector<BYTE> &w, unsigned &index, vector<char> &outputBuffer)
{
	unsigned num = dictionary.find(w)->second;
	BYTE *byteArray = IntToByteArray(num);
	char charArray[4];
	//memcpy(charArray, (char*)&num, 4);
	
	for (int i = 0; i < 4; i++)
		charArray[i] = ByteToChar(byteArray[i]);
	for (int i = 0; i < 4;i++)
	{
		outputBuffer.push_back(charArray[i]);
	}
	index++;
}