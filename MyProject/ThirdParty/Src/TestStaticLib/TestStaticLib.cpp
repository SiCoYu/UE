#include "TestStaticLib.h"
#include "stdio.h"

int TestStaticLib::testFunc()
{
	char aaa[20];
	sprintf(aaa, "%d", 10);
	return 5;
}