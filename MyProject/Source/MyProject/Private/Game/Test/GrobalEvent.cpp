#include "MyProject.h"
#include "GrobalEvent.h"
#include <iostream>

void GrobalEvent::SetUp()
{
	std::cout << "gtest GrobalEvent SetUp execute" << std::endl;
}

void GrobalEvent::TearDown()
{
	std::cout << "gtest GrobalEvent TearDown execute" << std::endl;
}