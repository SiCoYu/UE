#include "MyProject.h"
#include "TestGlocal.h"
#include <iostream>

MY_BEGIN_NAMESPACE(MyNS)

void SayHello(const char* to) 
{
	std::cout << "Hello, " << to << "!" << std::endl;
}

MY_END_NAMESPACE