#pragma once
typedef unsigned char BYTE;
class Node
{
public:
	int id;
	BYTE letter;
	int frequency;
	Node *left, *right;
	bool isLetter;

	Node() : id(0), letter(0), frequency(0), left(nullptr), 
		right(nullptr), isLetter(false) {}
	Node(BYTE letter, int frequency, Node *left, Node *right, 
		bool isLetter) : letter(letter), frequency(frequency), 
		left(left), right(right), isLetter(isLetter) {}
	~Node();
};

