#include "Compressor.h"
#include "Decompressor.h"
#include <fstream>

void GetOriginalData(string inputFileName, vector<char> &originalData);
void WriteDecoded(vector<char> &decodedData, string outputFileName);

int main()
{
	vector<char> originalData;// = { 'T', 'O', 'B', 'E', 'O', 'R', 'N', 'O', 'T', 'T', 'O', 'B', 'E', 'O', 'R', 'T', 'O', 'B', 'E', 'O', 'R', 'N', 'O', 'T' };
	vector<bool> encodedData;
	vector<char> decodedData;
	string inputFile = "big.txt";
	string compressedFile = inputFile + ".lzw";
	string decompressedFile = "decompressed" + inputFile;

	GetOriginalData(inputFile, originalData);

	Compressor::Compress(originalData, encodedData);
	Decompressor::Decompress(encodedData, decodedData);

	WriteDecoded(decodedData, decompressedFile);

	for(int i=0;i<originalData.size();i++)
	{
		if(originalData[i] != decodedData[i])
		{
			return 1;
		}
	}

	return 0;
}

void GetOriginalData(string inputFileName, vector<char> &originalData)
{
	originalData.clear();
	ifstream inputStream(inputFileName, ios::binary);
	char *buffer = new char[1024*1024];

	while(inputStream.read(buffer, 1024 * 1024))
	{
		for (int i = 0; i<inputStream.gcount(); i++)
		{
			originalData.push_back(buffer[i]);
		}
	}
	for(int i=0;i<inputStream.gcount();i++)
	{
		originalData.push_back(buffer[i]);
	}
	inputStream.close();
}

void WriteDecoded(vector<char> &decodedData, string outputFileName)
{
	ofstream outputStream(outputFileName, ios::binary);

	char *pointer = &decodedData[0];
	outputStream.write(pointer, decodedData.size());

	outputStream.close();
}