#include <fstream>
#include "Compressor.h"
#include "Decompressor.h"
using namespace std;

int main()
{
	string folder = "TestData\\";
	string inputFile = "dataFile.dat";
	string compressedFile = inputFile + ".huf";
	string decompressedFile = "decompressed" + inputFile;

	Compressor::Compress(folder + inputFile, folder + compressedFile);
	Decompressor::Decompress(folder + compressedFile, folder + decompressedFile);
	return 0;
}