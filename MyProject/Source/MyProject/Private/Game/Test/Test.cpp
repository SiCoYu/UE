#include "MyProject.h"
#include "Test.h"
#include "TestExtern.h"
#include "TestSocket.h"

#include "gtest/gtest.h"

Test::Test()
{
	m_testExtern = new TestExtern();
	m_testSocket = new TestSocket();
}

void Test::runTest()
{
	testing::InitGoogleTest((int*)nullptr, (char**)nullptr);
	RUN_ALL_TESTS();
}