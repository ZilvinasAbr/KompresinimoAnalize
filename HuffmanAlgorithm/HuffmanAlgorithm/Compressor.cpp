#include "Compressor.h"



Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

list<BYTE> Compressor::Compress(string inputFile, string outputFile)
{
	map<BYTE, int> frequencies = GetFrequencies(inputFile);
	
	list<Node*> letterLeaves = GetLetterLeavesList(frequencies);
	priority_queue<Node*> priority_queue = CreatePriorityQueue(letterLeaves);
	Node *root = CreateTree(priority_queue);
	string nullTerminatedCode;
	map<BYTE, string> letterStringMap = CreateLetterStringMap(root, nullTerminatedCode);

	ifstream inputStream(inputFile, ios::in | ios::binary);
	ofstream outputStream(outputFile, ios::out | ios::binary);
	ConvertTreeToBytes(outputStream, root);
	GetCompressedData(inputStream, outputStream, letterStringMap, nullTerminatedCode);
	outputStream.close();
	inputStream.close();
	return list<BYTE>();
}

list<BYTE> Compressor::GetCompressedData(ifstream &inputStream, ofstream &outputStream, const map<BYTE, string>& letterStringMap, string nullTerminatedCode)
{
	vector<bool> buffer;
	char charBuffer[1];
	BYTE byteBuffer;
	while(inputStream.read(charBuffer, 1))
	{
		byteBuffer = BYTE(charBuffer[0]);
		string code = letterStringMap.find(byteBuffer)->second;
		for(char &c : code)
		{
			buffer.push_back(c == '1' ? true : false);
			if(buffer.size() == 8)
			{
				char charToWrite[1];
				BYTE byteFromBools = int(buffer[0]) * 1 + int(buffer[1]) * 2 + 
					int(buffer[2]) * 4 + int(buffer[3]) * 8 + int(buffer[4]) * 16 + 
					int(buffer[5]) * 32 + int(buffer[6]) * 64 + int(buffer[7]) * 128;
				charToWrite[0] = char(byteFromBools);
				outputStream.write(charToWrite, 1);
				buffer.clear();
			}
		}
		for(char &c : nullTerminatedCode)
		{
			buffer.push_back(c == '1' ? true : false);
			if (buffer.size() == 8)
			{
				char charToWrite[1];
				BYTE byteFromBools = int(buffer[0]) * 1 + int(buffer[1]) * 2 +
					int(buffer[2]) * 4 + int(buffer[3]) * 8 + int(buffer[4]) * 16 +
					int(buffer[5]) * 32 + int(buffer[6]) * 64 + int(buffer[7]) * 128;
				charToWrite[0] = char(byteFromBools);
				outputStream.write(charToWrite, 1);
				buffer.clear();
			}
		}

		//writes out what is left from buffer as a byte
		int lastByte = 0;
		int multiplier = 1;
		for (int i = 0; i < buffer.size(); i++)
		{
			if (buffer[i])
				lastByte += multiplier;
			multiplier *= 2;
		}
		char charToWrite[1];
		charToWrite[0] = char(BYTE(lastByte));
		outputStream.write(charToWrite, 1);
	}

	return list<BYTE>();
}

map<BYTE, int> Compressor::GetFrequencies(string inputFile)
{
	ifstream inputStream(inputFile, ios::in, ios::binary);
	map<BYTE, int> frequencies;
	vector<bool> buffer;
	char charBuffer[1];
	BYTE byteBuffer;
	while (inputStream.read(charBuffer, 1))
	{
		byteBuffer = BYTE(charBuffer[0]);
		if (frequencies.find(byteBuffer) != frequencies.end())
			frequencies.find(byteBuffer)->second += 1;
		else
			frequencies.insert(pair<BYTE, int>(byteBuffer, 1));
	}

	return frequencies;
}

list<Node *> Compressor::GetLetterLeavesList(map<BYTE, int> &frequencies)
{
	list<Node*> letterLeaves;
	for(pair<BYTE, int> a : frequencies)
	{
		Node *n = new Node(a.first, a.second, nullptr, nullptr, true);
		letterLeaves.push_back(n);
	}
	return letterLeaves;
}

priority_queue<Node*> Compressor::CreatePriorityQueue(list<Node*> nodes)
{
	priority_queue<Node*> priority_queue;
	for (Node *n : nodes)
		priority_queue.push(n);
	return priority_queue;
}

Node* Compressor::CreateTree(priority_queue<Node*> priorityQueue)
{
	//Insert terminating node
	Node *newNode = new Node(0, 0, nullptr, nullptr, true);
	priorityQueue.push(newNode);
	while(priorityQueue.size() != 1)
	{
		Node *first = priorityQueue.top();
		priorityQueue.pop();
		Node *second = priorityQueue.top();
		priorityQueue.pop();
		Node *newNode2 = new Node(0, first->frequency + second->frequency, first, second, false);
		priorityQueue.push(newNode2);
	}
	Node *root = priorityQueue.top();
	priorityQueue.pop();
	return root;
}

map<BYTE, string> Compressor::CreateLetterStringMap(Node *root, string & nullTerminatedCode)
{
	// TODO: Change this stupid workaround of list<string>
	list<string> listOfOneString;
	map<BYTE, string> map;
	RecursiveCreateLetterStringMapHelper(map, root, "", listOfOneString);
	return map;
}

void Compressor::RecursiveCreateLetterStringMapHelper(map<BYTE, string> &map, Node * currentNode, string currentCode, list<string>& listOfOneString)
{
	if (currentNode == nullptr)
		return;
	string newCodeLeft = currentCode + "0";
	string newCodeRight = currentCode + "1";
	RecursiveCreateLetterStringMapHelper(map, currentNode->left, newCodeLeft, listOfOneString);
	if(currentNode->isLetter)
	{
		if (currentNode->frequency != 0) // this is needed, so that the '\0' terminating node wouldn't be mapped
			map.insert(pair<BYTE, string>(currentNode->letter, currentCode));
		else
			listOfOneString.push_back(currentCode);
	}
	RecursiveCreateLetterStringMapHelper(map, currentNode->right, newCodeRight, listOfOneString);
}

void Compressor::ConvertTreeToBytes(ofstream &outputStream, Node *root)
{
	vector<BYTE> bytesList;
	vector<MinimalNode> minimalNodes = CompressTree(root);
	BYTE *lengthInBytes = IntToByteArray(minimalNodes.size());
	for (int i = 0; i < 4; i++)
		bytesList.push_back(lengthInBytes[i]);
	delete[] lengthInBytes;
	for(MinimalNode &n : minimalNodes)
	{
		BYTE letterByte = n.letter;
		BYTE *leftBytes = IntToByteArray(n.left);
		BYTE *rightBytes = IntToByteArray(n.right);
		bytesList.push_back(n.letter);
		for (int i = 0; i < 4; i++)
			bytesList.push_back(leftBytes[i]);
		for (int i = 0; i < 4; i++)
			bytesList.push_back(rightBytes[i]);
		delete[] leftBytes;
		delete[] rightBytes;
	}

	BYTE* bytesArray = &bytesList[0];
	char* charArray = reinterpret_cast<char*>(&bytesArray);
	outputStream.write(charArray, bytesList.size());
}

vector<MinimalNode> Compressor::CompressTree(Node *root)
{
	vector<Node *> nodes;
	RecursiveCompressTree(root, nodes);
	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->id = i;
	vector<MinimalNode> result(nodes.size());
	for (int i = 0; i < result.size(); i++)
	{
		if (nodes[i]->frequency == 0)//if it is terminating symbol, make left and right ints equal -2
		{
			int left = -2;
			int right = -2;
			result[i] = MinimalNode(nodes[i]->letter, left, right);
		}else
		{
			int left = (nodes[i]->left == nullptr) ? -1 : nodes[i]->left->id;
			int right = (nodes[i]->right == nullptr) ? -1 : nodes[i]->right->id;
			result[i] = MinimalNode(nodes[i]->letter, left, right);
		}	
	}
	return result;
}

void Compressor::RecursiveCompressTree(Node *currentNode, vector<Node*> &nodes)
{
	if (currentNode == nullptr)
		return;
	nodes.push_back(currentNode);
	RecursiveCompressTree(currentNode->left, nodes);
	RecursiveCompressTree(currentNode->right, nodes);
}

BYTE* Compressor::IntToByteArray(int integer)
{
	BYTE *byteArray = new BYTE[4];
	byteArray[3] = integer % 256;
	integer /= 256;
	byteArray[2] = integer % 256;
	integer /= 256;
	byteArray[1] = integer % 256;
	integer /= 256;
	byteArray[0] = integer;
	return byteArray;
}