#include "MyProject.h"
#include "TestExtern.h"
#include "Templates/Casts.h"

#define dynamic_cast aaa

TestExtern::TestExtern()
{
	//m_testStaticLibB = new TestStaticLibB();
	//m_testStaticLibB->testFunc("aaaaaaa");

	//m_testStaticLibA = dynamic_cast<TestStaticLibA*>(m_testStaticLibB);
	//m_testStaticLibA->testFunc("aaaaaaa");

	m_testStaticLibA = new TestStaticLibB();
	m_testStaticLibA->testFunc("aaaaaaa");

	m_testStaticLibB = (TestStaticLibB*)m_testStaticLibA;
	m_testStaticLibA->testFunc("aaaaaaa");
}
