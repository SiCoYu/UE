#include "MyProject.h"
#include "Test.h"
#include "TestExtern.h"
#include "TestSocket.h"

#include "gtest/gtest.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <shellapi.h>
#include "Windows/HideWindowsPlatformTypes.h"

Test::Test()
{
	m_testExtern = new TestExtern();
	m_testSocket = new TestSocket();
}

void Test::runTest()
{
	const TCHAR* CmdLine = GetCommandLine();
	LPWSTR *szArgList;
	int argCount;
	szArgList = CommandLineToArgvW(CmdLine, &argCount);
	testing::InitGoogleTest(&argCount, szArgList);

	//testing::InitGoogleTest(__argc, __argv);
	RUN_ALL_TESTS();
}