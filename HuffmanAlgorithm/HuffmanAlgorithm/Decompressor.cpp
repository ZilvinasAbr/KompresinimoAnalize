#include "Decompressor.h"
#include <vector>


Decompressor::Decompressor()
{
}


Decompressor::~Decompressor()
{
}

void Decompressor::Decompress(string inputFile, string outputFile)
{
	ifstream input(inputFile, ios::in | ios::binary);
	ofstream output(outputFile, ios::out, ios::binary);
	char lengthChars[4];
	BYTE lenghtBytes[4];
	input.read(lengthChars, 4);
	memcpy(&lenghtBytes, lengthChars, 4);

	/*if (BitConverter.IsLittleEndian)
	Array.Reverse(lenghtBytes);*/
	int lenght = 0;// = BitConverter.ToInt32(lenghtBytes, 0);
	memcpy(&lenght, lenghtBytes, sizeof(int));
	/*for (int i = 0; i < 4; ++i)
	{
		lenght += lenghtBytes[i];
	}*/
		
	vector<MinimalNode> minimalNodes;
	for (int i = 0; i < lenght; i++)
	{
		BYTE letterByte;
		char letterChar[1];
		input.read(letterChar, 1);
		letterByte = BYTE(letterChar[0]);
		char leftChars[4] = { 0,0,0,0 };
		char rightChars[4] = { 0,0,0,0 };
		input.read(leftChars, 4);
		input.read(rightChars, 4);
		//BYTE leftBytes[4];
		//BYTE rightBytes[4];
		//memcpy(leftBytes, leftChars, 4);
		//memcpy(rightBytes, rightChars, 4);

		if (false/*BitConverter.IsLittleEndian*/)
		{
			/*Array.Reverse(letterBytes);
			Array.Reverse(leftBytes);
			Array.Reverse(rightBytes);*/
		}
		int left, right;
		if(leftChars[1] == 0 && leftChars[2] == 0 && leftChars[3] == 0)
		{
			left = int(leftChars[0]);
		}else
		{
			memcpy(&left, leftChars, sizeof(int));
		}

		if (rightChars[1] == 0 && rightChars[2] == 0 && rightChars[3] == 0)
		{
			right = int(rightChars[0]);
		}
		else
		{
			memcpy(&right, rightChars, sizeof(int));
		}
		minimalNodes.push_back(MinimalNode(letterByte, left, right));
	}
	char charBuffer[1];
	int currentNode = 0;
	while(input.read(charBuffer, 1))
	{
		BYTE byteBuffer = BYTE(charBuffer[0]);
		bool booleans[8];
		for (int i = 0; i < 8;i++)
		{
			booleans[i] = byteBuffer % 2;
			byteBuffer /= 2;
		}
		for (int i = 0; i < 8;i++)
		{
			if(booleans[i])
			{
				currentNode = minimalNodes[currentNode].right;
				if(minimalNodes[currentNode].left == minimalNodes[currentNode].right && minimalNodes[currentNode].left == -1)
				{
					char tempCharArray[1];
					tempCharArray[0] = char(minimalNodes[currentNode].letter);
					output.write(tempCharArray, 1);
					currentNode = 0;
				}
				else if (minimalNodes[currentNode].left == minimalNodes[currentNode].right && minimalNodes[currentNode].left == -2) //if it is terminating symbol
				{
					i = 7; //end the for loop
					goto end;
				}
			}else
			{
				currentNode = minimalNodes[currentNode].left;
				if (minimalNodes[currentNode].left == minimalNodes[currentNode].right && minimalNodes[currentNode].left == -1)
				{
					char tempCharArray[1];
					tempCharArray[0] = char(minimalNodes[currentNode].letter);
					output.write(tempCharArray, 1);
					currentNode = 0;
				}
				else if (minimalNodes[currentNode].left == minimalNodes[currentNode].right && minimalNodes[currentNode].left == -2) //if it is terminating symbol
				{
					i = 7; //end the for loop
					goto end;
				}
			}
		}
	}
	end:
	input.close();
	output.close();
}
