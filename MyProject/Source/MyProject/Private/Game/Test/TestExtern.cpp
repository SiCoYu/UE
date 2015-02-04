#include "MyProject.h"
#include "TestExtern.h"

TestExtern::TestExtern()
{
	m_testStaticLib = new TestStaticLib();
	m_testStaticLib->testFunc();
}
