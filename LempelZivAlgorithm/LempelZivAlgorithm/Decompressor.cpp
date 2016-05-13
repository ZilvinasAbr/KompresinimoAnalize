#include "Decompressor.h"
#include <vector>
#include <iostream>
#include "DecompressorHelpers.h"
using namespace std;

Decompressor::Decompressor()
{
}


Decompressor::~Decompressor()
{
}

void Decompressor::Decompress(vector<bool> &encodedData, vector<char> &decodedData)
{
	vector< vector<char> > dictionary = InitializeDictionary(); //Initialize dictionary
	vector<char> outputSequence;
	vector<char> entry;
	int decimalCounter = 255;
	int temp = 0;
	outputSequence = Read(encodedData, temp, dictionary, decimalCounter++);
	decodedData.insert(decodedData.end(), outputSequence.begin(), outputSequence.end());
	entry.insert(entry.end(), outputSequence.begin(), outputSequence.end());
	int aaaaa = 5;

	for(int i=8;i<encodedData.size();)
	{
		outputSequence = Read(encodedData, i, dictionary, decimalCounter);
		if(outputSequence[0] == 'O')
		{
			int aaa = 5;
		}
		decodedData.insert(decodedData.end(), outputSequence.begin(), outputSequence.end());
		entry.insert(entry.end(), outputSequence.begin(), outputSequence.begin()+1);
		dictionary.push_back(entry);
		decimalCounter++;
		entry.clear();
		entry.insert(entry.end(), outputSequence.begin(), outputSequence.end());
	}
	std::cout << aaaaa;

}