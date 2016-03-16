#include "Compressor.h"
#include "Decompressor.h"

int main()
{
	string inputFile = "longText.txt";
	string compressedFile = inputFile + ".huf";
	string decompressedFile = "decompressed" + inputFile;
	Compressor::Compress(inputFile, compressedFile);
	Decompressor::Decompress(compressedFile, decompressedFile);
	return 0;
}