#include "MyProject.h"
#include "TestExtern.h"

TestExtern::TestExtern()
{
	m_testStaticLibB = new TestStaticLibB();
	m_testStaticLibB->testFunc("aaaaaaa");

	m_testStaticLibA = dynamic_cast<TestStaticLibA*>(m_testStaticLibB);
	m_testStaticLibA->testFunc("aaaaaaa");
}
