#include "TestStaticLibA.h"
#include <stdio.h>


int TestStaticLibA::testFunc(std::string bbb)
{
	char aaa[20];
	sprintf(aaa, "%s %d", bbb, 10);
	return 5;
}