#include <fstream>
#include "Compressor.h"
using namespace std;

int main()
{
	string inputFile = "text.txt";
	string outputFile = "compressed.huf";
	Compressor::Compress(inputFile, outputFile);
	return 0;
}