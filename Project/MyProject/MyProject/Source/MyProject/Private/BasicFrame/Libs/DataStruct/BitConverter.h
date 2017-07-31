#ifndef __BitConverter_H
#define __BitConverter_H

#include "MyProject.h"

class BitConverter
{
public:
	static char ToChar(char* value, int startIndex);
	static int16 ToInt16(char* value, int startIndex);
	static int32 ToInt32(char* value, int startIndex);
	static int64 ToInt64(char* value, int startIndex);

	static uint16 ToUInt16(char* value, int startIndex);
	static uint32 ToUInt32(char* value, int startIndex);
	static uint64 ToUInt64(char* value, int startIndex);

	static float ToSingle(char* value, int startIndex);
	static double ToDouble(char* value, int startIndex);

	static int32 swapByteOrder(int32 value);
	static int64 swapByteOrder(int64 value);
	static uint16 swapByteOrder(uint16 value);
	static uint32 swapByteOrder(uint32 value);
	static double swapByteOrder(double value);
};

#endif