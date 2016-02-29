#pragma once
typedef unsigned char BYTE;

inline BYTE* IntToByteArray(unsigned integer)
{
	BYTE* byteArray = new BYTE[4];
	byteArray[3] = integer % 256;
	integer /= 256;
	byteArray[2] = integer % 256;
	integer /= 256;
	byteArray[1] = integer % 256;
	integer /= 256;
	byteArray[0] = integer;
	return byteArray;
}

inline unsigned ByteArraytoUnsignedInt(BYTE array[4])
{
	unsigned result = 0;
	result += array[3];
	result += static_cast<unsigned>(array[2]) * 256;
	result += static_cast<unsigned>(array[1]) * 256 * 256;
	result += static_cast<unsigned>(array[0]) * 256 * 256 * 256;
	return result;
}



inline char ByteToChar(BYTE c)
{
	if (c > 127)
	{
		int temp = (256 - c)*-1;
		return temp;
	}
	else
		return c;
}
inline BYTE CharToByte(char c)
{
	int temp = c;
	if (temp > 0)
		return temp;
	else
		return temp * -2;
}