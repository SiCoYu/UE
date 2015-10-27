#include "MyProject.h"
#include "BitConverter.h"

char BitConverter::ToChar(char* value, int startIndex)
{
	return value[startIndex];
}

int16 BitConverter::ToInt16(char* value, int startIndex)
{
	return 0;
}

int32 BitConverter::ToInt32(char* value, int startIndex)
{
	return 0;
}

int64 BitConverter::ToInt64(char* value, int startIndex)
{
	return 0;
}

uint16 BitConverter::ToUInt16(char* value, int startIndex)
{
	return 0;
}

uint32 BitConverter::ToUInt32(char* value, int startIndex)
{
	return 0;
}

uint64 BitConverter::ToUInt64(char* value, int startIndex)
{
	return 0;
}

float BitConverter::ToSingle(char* value, int startIndex)
{
	return 0;
}

double BitConverter::ToDouble(char* value, int startIndex)
{
	return 0;
}

int32 BitConverter::swapByteOrder(int32 value)
{
	int32 swap = (int32)((0x000000FF) & (value >> 24)
		| (0x0000FF00) & (value >> 8)
		| (0x00FF0000) & (value << 8)
		| (0xFF000000) & (value << 24));
	return swap;
}

int64 BitConverter::swapByteOrder(int64 value)
{
	uint64 uvalue = (uint64)value;
	uint64 swap = ((0x00000000000000FF) & (uvalue >> 56)
		| (0x000000000000FF00) & (uvalue >> 40)
		| (0x0000000000FF0000) & (uvalue >> 24)
		| (0x00000000FF000000) & (uvalue >> 8)
		| (0x000000FF00000000) & (uvalue << 8)
		| (0x0000FF0000000000) & (uvalue << 24)
		| (0x00FF000000000000) & (uvalue << 40)
		| (0xFF00000000000000) & (uvalue << 56));

	return (int64)swap;
}

uint16 BitConverter::swapByteOrder(uint16 value)
{
	return (uint16)((0x00FF & (value >> 8))
		| (0xFF00 & (value << 8)));
}

uint32 BitConverter::swapByteOrder(uint32 value)
{
	uint32 swap = ((0x000000FF) & (value >> 24)
		| (0x0000FF00) & (value >> 8)
		| (0x00FF0000) & (value << 8)
		| (0xFF000000) & (value << 24));
	return swap;
}

double BitConverter::swapByteOrder(double value)
{
	//Byte[] buffer = BitConverter.GetBytes(value);
	//Array.Reverse(buffer, 0, buffer.Length);
	//return BitConverter.ToDouble(buffer, 0);
	return 0;
}