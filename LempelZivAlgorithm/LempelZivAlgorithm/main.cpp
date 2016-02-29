#include <iostream>
#include "Compressor.h"
#include "Decompressor.h"

int main()
{
	Compressor::Compress("text.txt", "output.lzw");
	Decompressor::Decompress("output.lzw", "textDecompressed.txt");
	return 0;
}