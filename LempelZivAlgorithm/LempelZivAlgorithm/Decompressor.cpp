#include "Decompressor.h"



Decompressor::Decompressor()
{
}


Decompressor::~Decompressor()
{
}


/*
read a charakter k;
output k;
w = k;
while( read a character k )
entry = dictionary entry for k;
output entry;
add w + entry[0] to dictionary;
w = entry;
*/
void Decompressor::Decompress(string inputFile, string outputFile)
{
	unsigned index = 256;
	ifstream inputFileStream(inputFile.c_str(), ios::in | ios::binary);
	ofstream outputFileStream(outputFile.c_str(), ios::out | ios::binary);
	map< unsigned, vector<BYTE> > dictionary;
	vector<BYTE> previousOutput;
	InitializeDictionary(dictionary);
	char buffer[4];
	BYTE byteBuffer[4];
	while (inputFileStream.read(buffer, 4)) {
		for (int i = 0; i < 4; i++)
			byteBuffer[i] = CharToByte(buffer[i]);
		unsigned uinteger = ByteArraytoUnsignedInt(byteBuffer);
		//std::map< unsigned, vector<char> >::iterator it = dictionary.find(uinteger);
		vector<BYTE> outputSequence = dictionary.find(uinteger)->second;
		BYTE* outputArray = &outputSequence[0];
		char *outputCharArray = new char[outputSequence.size()];
		for (int i = 0; i < outputSequence.size(); i++)
			outputCharArray[i] = ByteToChar(outputSequence[i]);
		outputFileStream.write(outputCharArray, outputSequence.size());
		vector<BYTE> newSequence = previousOutput;
		newSequence.push_back(outputSequence[0]);
		dictionary.insert(pair<unsigned, vector<BYTE> >(index, newSequence));
		index++;
		previousOutput = outputSequence;
	}
	inputFileStream.close();
	outputFileStream.close();
}

void Decompressor::InitializeDictionary(map< unsigned, vector<BYTE> > &dictionary)
{
	for (unsigned i = 0; i < 256; i++) {
		vector<BYTE> a;
		a.push_back(i);
		dictionary.insert(pair<unsigned, vector<BYTE> >(i, a));
	}
}
