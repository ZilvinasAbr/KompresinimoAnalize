#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <list>
#include "Node.h"
#include "MinimalNode.h"
typedef unsigned char BYTE;
using namespace std;

class Compressor
{
public:
	Compressor();
	~Compressor();
	static list<BYTE> Compress(string inputFile, string outputFile);
private:
	static list<BYTE> GetCompressedData(ifstream &inputStream, ofstream &outputStream, const map<BYTE, string>& letterStringMap, string nullTerminatedCode);
	static map<BYTE, int> GetFrequencies(string inputFile);
	static list<Node *> GetLetterLeavesList(map<BYTE, int> &frequencies);
	static priority_queue<Node*> Compressor::CreatePriorityQueue(list<Node*> nodes);
	static Node* Compressor::CreateTree(priority_queue<Node*> priorityQueue);
	static map<BYTE, string> CreateLetterStringMap(Node *root, string & nullTerminatedCode);
	static void RecursiveCreateLetterStringMapHelper(map<BYTE, string> &map, Node *currentNode, string currentCode, list<string> &listOfOneString);
	static void ConvertTreeToBytes(ofstream &outputStream, Node *root);
	static vector<MinimalNode> CompressTree(Node *root);
	static void RecursiveCompressTree(Node *currentNode, vector<Node*> &nodes);
	static BYTE* IntToByteArray(int integer);
};

