#include "TestStaticLibB.h"
#include <stdio.h>


int TestStaticLibB::testFunc(std::string bbb)
{
	char aaa[20];
	sprintf(aaa, "%s %d", bbb, 10);
	return 5;
}