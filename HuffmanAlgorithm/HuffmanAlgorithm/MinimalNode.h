#pragma once
typedef unsigned char BYTE;
class MinimalNode
{
public:
	BYTE letter;
	int left, right;
	MinimalNode(): letter(0), left(0), right(0) {}
	MinimalNode(BYTE letter, int left, int right) : letter(letter),
		left(left), right(right) {}
	~MinimalNode();
private:

};

