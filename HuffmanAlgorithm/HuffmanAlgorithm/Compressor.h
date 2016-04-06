#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <list>
#include "Node.h"
#include "MinimalNode.h"
#include "Compare.h"
#include "Helper.h"
typedef unsigned char BYTE;
using namespace std;

class Compressor
{
public:
	Compressor();
	~Compressor();
	static list<BYTE> Compress(string inputFile, string outputFile);
private:
	static void GetCompressedData(ifstream &inputStream, ofstream &outputStream, const vector<string> &letterStringMap, string nullTerminatedCode);
	static vector<int> GetFrequencies(string inputFile);
	static list<Node *> GetLetterLeavesList(vector<int> &frequencies);
	static priority_queue<Node*, vector<Node*>, Compare> Compressor::CreatePriorityQueue(list<Node*> nodes);
	static Node* CreateTree(priority_queue<Node*, vector<Node*>, Compare> priorityQueue);
	static vector<string> CreateLetterStringMap(Node *root, string & nullTerminatedCode);
	static void RecursiveCreateLetterStringMapHelper(vector<string> &map, Node *currentNode, string currentCode, vector<string> &listOfOneString);
	static void ConvertTreeToBytes(ofstream &outputStream, Node *root);
	static vector<MinimalNode> CompressTree(Node *root);
	static void RecursiveCompressTree(Node *currentNode, vector<Node*> &nodes);
	//static BYTE* IntToByteArray(int integer);
	static void GetCompressedData2(ifstream &inputStream, ofstream &outputStream, vector<string>& letterStringMap, string nullTerminatedCode);
};

