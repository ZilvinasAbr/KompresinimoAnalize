#include "Compressor.h"



Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

list<BYTE> Compressor::Compress(string inputFile, string outputFile)
{
	vector<int> frequencies = GetFrequencies(inputFile);
	
	list<Node*> letterLeaves = GetLetterLeavesList(frequencies);
	priority_queue<Node*, std::vector<Node*>, Compare> priority_queue = CreatePriorityQueue(letterLeaves);
	Node *root = CreateTree(priority_queue);
	string nullTerminatedCode;
	vector<string> letterStringMap = CreateLetterStringMap(root, nullTerminatedCode);

	ifstream inputStream(inputFile, ios_base::binary);
	ofstream outputStream(outputFile, ios_base::binary);
	ConvertTreeToBytes(outputStream, root);
	GetCompressedData2(inputStream, outputStream, letterStringMap, nullTerminatedCode);
	outputStream.close();
	inputStream.close();
	return list<BYTE>();
}

void Compressor::GetCompressedData2(ifstream &inputStream, ofstream &outputStream, vector<string>& letterStringMap, string nullTerminatedCode)
{
	const int bufferLength = 1024 * 1024;
	char *buffer = new char[bufferLength];
	vector<BYTE*> toCompress;
	list<bool> compressed;
	list< vector<bool> > tempExperiment;
	vector< vector<bool> > letterBooleansMap = LetterStringToBoolMapper(letterStringMap);
	while (inputStream.read(buffer, bufferLength))
	{
		for (int i = 0; i < bufferLength;i++)
		{
			vector<bool> booleans = letterBooleansMap[BYTE(buffer[i])];
			compressed.insert(compressed.end(), booleans.begin(), booleans.end());
			/*string code = letterStringMap[BYTE(buffer[i])];
			for (char &c : code)
				compressed.push_back(c == '1' ? true : false);*/
			//InsertBools(letterStringMap[BYTE(buffer[i])], compressed);
			
		}
	}
	streamsize count = inputStream.gcount();
	for (int i = 0; i < count; i++)
	{
		vector<bool> booleans = letterBooleansMap[BYTE(buffer[i])];
		compressed.insert(compressed.end(), booleans.begin(), booleans.end());
		/*string code = letterStringMap[BYTE(buffer[i])];
		for (char &c : code)
			compressed.push_back(c == '1' ? true : false);*/
		//InsertBools(letterStringMap[BYTE(buffer[i])], compressed);
	}
	InsertBools(nullTerminatedCode, compressed);
	int moreToAdd = 8 - compressed.size() % 8;
	if(moreToAdd != 8 && moreToAdd != 0)
		for (int i = 0; i < moreToAdd;i++)
			compressed.push_back(false);
	char *chars = new char[compressed.size() / 8];
	memcpy(chars, &compressed, compressed.size() / 8);
	outputStream.write(chars, compressed.size() / 8);
	delete[] chars;
	delete[] buffer;
}




void Compressor::GetCompressedData(ifstream &inputStream, ofstream &outputStream, const vector<string>& letterStringMap, string nullTerminatedCode)
{
	vector<bool> buffer;
	const int bufferLength = 1024 * 1024;
	char *inputCharBuffer = new char[bufferLength] {};
	vector<char> outputCharBuffer;
	BYTE byteBuffer;
	while (inputStream.read(inputCharBuffer, bufferLength))
	{
		
		for (int i = 0; i < bufferLength;i++)
		{
			byteBuffer = BYTE(inputCharBuffer[i]);//1
			string code = letterStringMap[byteBuffer];//1
			for(char &c : code)//8
			{
				buffer.push_back(c == '1' ? true : false);//8
				if (buffer.size() == 8)//1
				{
					char charToWrite[1];//1
					BYTE byteFromBools = int(buffer[0]) * 1 + int(buffer[1]) * 2 +
						int(buffer[2]) * 4 + int(buffer[3]) * 8 + int(buffer[4]) * 16 +
						int(buffer[5]) * 32 + int(buffer[6]) * 64 + int(buffer[7]) * 128;
					charToWrite[0] = char(byteFromBools);
					outputCharBuffer.push_back(charToWrite[0]);
					//outputStream.write(charToWrite, 1);
					buffer.clear();
				}
			}
		}
		char *temp = &outputCharBuffer[0];
		outputStream.write(temp, outputCharBuffer.size());
		outputCharBuffer.clear();
	}
	auto readCount = inputStream.gcount();
	for (auto i = 0; i < readCount; i++)
	{
		byteBuffer = BYTE(inputCharBuffer[i]);
		string code = letterStringMap[byteBuffer];
		for (char &c : code)
		{
			buffer.push_back(c == '1' ? true : false);
			if (buffer.size() == 8)
			{
				char charToWrite[1];
				BYTE byteFromBools = int(buffer[0]) * 1 + int(buffer[1]) * 2 +
					int(buffer[2]) * 4 + int(buffer[3]) * 8 + int(buffer[4]) * 16 +
					int(buffer[5]) * 32 + int(buffer[6]) * 64 + int(buffer[7]) * 128;
				charToWrite[0] = char(byteFromBools);
				outputCharBuffer.push_back(charToWrite[0]);
				//outputStream.write(charToWrite, 1);
				buffer.clear();
			}
		}
	}
	char *temp = &outputCharBuffer[0];
	outputStream.write(temp, outputCharBuffer.size());
	outputCharBuffer.clear();

	for (char &c : nullTerminatedCode)
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


	//OLD IMPLEMENTATION
	/*vector<bool> buffer;
	char charBuffer[1];
	BYTE byteBuffer;
	while(inputStream.read(charBuffer, 1))
	{
		byteBuffer = BYTE(charBuffer[0]);
		string code = letterStringMap[byteBuffer];
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
	}
	for (char &c : nullTerminatedCode)
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
	outputStream.write(charToWrite, 1);*/
}

vector<int> Compressor::GetFrequencies(string inputFile)
{
	ifstream inputStream(inputFile, ios_base::binary);
	const int bufferLength = 1024 * 1024;
	vector<int> frequencies(256);
	vector<bool> buffer;
	char *charBuffer = new char[bufferLength];
	BYTE byteBuffer;
	//BYTE byteBuffer;

	while(inputStream.read(charBuffer, bufferLength))
	{
		for (int i = 0; i < bufferLength;i++)
		{
			byteBuffer = BYTE(charBuffer[i]);
			frequencies[byteBuffer] += 1;
		}
	}
	streamsize successfulyReadCharsCount = inputStream.gcount();
	for (int i = 0; i < successfulyReadCharsCount;i++)
	{
		byteBuffer = BYTE(charBuffer[i]);
		frequencies[byteBuffer] += 1;
	}
	inputStream.close();
	//return frequencies;
	return frequencies;
	
	//OLD IMPLEMENTATION
	/*ifstream inputStream(inputFile, ios_base::binary);
	map<BYTE, int> frequencies;
	vector<bool> buffer;
	char charBuffer[1];
	BYTE byteBuffer;
	
	inputStream.read(charBuffer, 1);
	int count = inputStream.gcount();
	while(inputStream.gcount() != 0)
	{
		byteBuffer = BYTE(charBuffer[0]);
		if (frequencies.find(byteBuffer) != frequencies.end())
			frequencies.find(byteBuffer)->second += 1;
		else
			frequencies.insert(pair<BYTE, int>(byteBuffer, 1));
		inputStream.read(charBuffer, 1);
	}
	inputStream.close();
	return frequencies;*/
}

list<Node *> Compressor::GetLetterLeavesList(vector<int> &frequencies)
{
	list<Node*> letterLeaves;
	for (int i = 0; i < frequencies.size();i++)
	{
		if(frequencies[i] != 0)
		{
			Node *n = new Node(i, frequencies[i], nullptr, nullptr, true);
			letterLeaves.push_back(n);
		}
	}
	/*for(pair<BYTE, int> a : frequencies)
	{
		Node *n = new Node(a.first, a.second, nullptr, nullptr, true);
		letterLeaves.push_back(n);
	}*/
	return letterLeaves;
}

priority_queue<Node*, vector<Node*>, Compare> Compressor::CreatePriorityQueue(list<Node*> nodes)
{
	priority_queue<Node*, vector<Node*>, Compare> priority_queue;
	for (Node *n : nodes)
		priority_queue.push(n);
	return priority_queue;
}

Node* Compressor::CreateTree(priority_queue<Node*, vector<Node*>, Compare> priorityQueue)
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

vector<string> Compressor::CreateLetterStringMap(Node *root, string & nullTerminatedCode)
{
	// TODO: Change this stupid workaround of list<string>
	vector<string> listOfOneString;
	vector<string> map(256);
	RecursiveCreateLetterStringMapHelper(map, root, "", listOfOneString);
	nullTerminatedCode = listOfOneString[0];
	return map;
}

void Compressor::RecursiveCreateLetterStringMapHelper(vector<string> &map, Node * currentNode, string currentCode, vector<string>& listOfOneString)
{
	if (currentNode == nullptr)
		return;
	string newCodeLeft = currentCode + "0";
	string newCodeRight = currentCode + "1";
	RecursiveCreateLetterStringMapHelper(map, currentNode->left, newCodeLeft, listOfOneString);
	if(currentNode->isLetter)
	{
		if (currentNode->frequency != 0) // this is needed, so that the '\0' terminating node wouldn't be mapped
			map[currentNode->letter] = currentCode;
		else
			listOfOneString.push_back(currentCode);
	}
	RecursiveCreateLetterStringMapHelper(map, currentNode->right, newCodeRight, listOfOneString);
}

void Compressor::ConvertTreeToBytes(ofstream &outputStream, Node *root)
{
	vector<BYTE> bytesList;
	vector<MinimalNode> minimalNodes = CompressTree(root);
	int minimalNodesSize = minimalNodes.size();
	char lengthInChars[4] = { 0,0,0,0 };
	memcpy(lengthInChars, &minimalNodesSize, sizeof(int));
	outputStream.write(lengthInChars, 4);
	for(MinimalNode &n : minimalNodes)
	{
		char letterChar[1] = { 0 };
		char leftChars[4] = { 0,0,0,0 };
		char rightChars[4] = { 0,0,0,0 };
		letterChar[0] = char(n.letter);
		memcpy(leftChars, &n.left, sizeof(int));
		memcpy(rightChars, &n.right, sizeof(int));
		outputStream.write(letterChar, 1);
		outputStream.write(leftChars, 4);
		outputStream.write(rightChars, 4);
	}
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