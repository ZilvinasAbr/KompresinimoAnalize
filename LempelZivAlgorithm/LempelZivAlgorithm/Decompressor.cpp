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

//patobulintas pseudokodas:

/*read a character k;
output k;
w = k;
while (read a character k)
// k could be a character or a code.
{
	if k exists in the dictionary
		entry = dictionary entry for k;
	output entry;
	add w + entry[0] to dictionary;
	w = entry;
	else
		output entry = w + firstCharacterOf(w);
	add entry to dictionary;
	w = entry;
}

//

read code k;
output k;
w = dictionary[k];
while (read code k)
	output dictionary[k]
	add w + dictionary[k][0] to dictionary
	w = dictionary[k]



*/
void Decompressor::Decompress(string inputFile, string outputFile)
{
	#pragma region Initialize
	unsigned index = 256;
	ifstream inputFileStream(inputFile.c_str(), ios::in | ios::binary);
	ofstream outputFileStream(outputFile.c_str(), ios::out | ios::binary);
	map< unsigned, vector<BYTE> > dictionary;
	vector<BYTE> previousOutput;
	InitializeDictionary(dictionary);
	vector<BYTE> w;
	unsigned k;
	//unsigned k, w;
	map< unsigned, vector<BYTE> >::iterator entry;
	#pragma endregion

	ReadK(inputFileStream, k);
	OutputK(outputFileStream, dictionary, k);
	w = dictionary.find(k)->second; // w = k;
	while (ReadK(inputFileStream, k)) {
		//for (int i = 0; i < 4; i++)
			//byteBuffer[i] = CharToByte(buffer[i]);
		//unsigned uinteger = ByteArraytoUnsignedInt(byteBuffer);
		////std::map< unsigned, vector<char> >::iterator it = dictionary.find(uinteger);
		
		//vector<BYTE> outputSequence = dictionary.find(uinteger)->second;
		//BYTE* outputArray = &outputSequence[0];
		//char *outputCharArray = new char[outputSequence.size()];
		//for (int i = 0; i < outputSequence.size(); i++)
			//outputCharArray[i] = ByteToChar(outputSequence[i]);
		//outputFileStream.write(outputCharArray, outputSequence.size());
		entry = dictionary.find(k);
		if(entry == dictionary.end())
		{
			int stopHere = 12;
		}
		OutputByteVector(outputFileStream, entry->second);
		AddNewEntry(dictionary, entry->second[0], w, index);
		w = entry->second;
		//vector<BYTE> newSequence = previousOutput;
		//newSequence.push_back(outputSequence[0]);
		//dictionary.insert(pair<unsigned, vector<BYTE> >(index, newSequence));
		//index++;
		//previousOutput = outputSequence;
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

bool Decompressor::ReadK(ifstream &inputFileStream, unsigned &k)
{
	char buffer[4];
	BYTE byteBuffer[4];
	if (!inputFileStream.read(buffer, 4))
		return false;
	for (int i = 0; i < 4; i++)
		byteBuffer[i] = CharToByte(buffer[i]);
	k = ByteArraytoUnsignedInt(byteBuffer);
	return true;
}

void Decompressor::OutputK(ofstream &outputFileStream, map< unsigned, vector<BYTE> > &dictionary, unsigned k)
{
	auto it = dictionary.find(k);
	OutputByteVector(outputFileStream, it->second);
}

void Decompressor::OutputByteVector(ofstream &outputFileStream, vector<BYTE> &byteVector)
{
	char *outputCharArray = new char[byteVector.size()];
	for (int i = 0; i < byteVector.size(); i++)
		outputCharArray[i] = ByteToChar(byteVector[i]);
	outputFileStream.write(outputCharArray, byteVector.size());
}

void Decompressor::AddNewEntry(map< unsigned, vector<BYTE> > &dictionary, BYTE &newByte, vector<BYTE> w, unsigned &index)
{
	vector<BYTE> newW = w;
	newW.push_back(newByte);
	dictionary.insert(pair<unsigned, vector<BYTE> >(index, newW));
	index++;
}