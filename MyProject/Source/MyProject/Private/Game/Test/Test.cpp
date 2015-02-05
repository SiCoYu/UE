#include "MyProject.h"
#include "Test.h"
#include "TestExtern.h"
#include "TestSocket.h"

Test::Test()
{
	m_testExtern = new TestExtern();
	m_testSocket = new TestSocket();
}