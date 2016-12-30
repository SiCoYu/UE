#include "MyProject.h"
#include "TestMain.h"
#include "TestExtern.h"
#include "TestSocket.h"
#include "TestUI.h"

#include "gtest/gtest.h"
#include "GrobalEvent.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <shellapi.h>
#include "Windows/HideWindowsPlatformTypes.h"

TestMain::TestMain()
{
	mTestExtern = new TestExtern();
	mTestSocket = new TestSocket();
	mTestUI = new TestUI();
}

void TestMain::runTest()
{
	const TCHAR* CmdLine = GetCommandLine();
	LPWSTR *szArgList;
	int argCount;
	szArgList = CommandLineToArgvW(CmdLine, &argCount);

	testing::AddGlobalTestEnvironment(new GrobalEvent);
	testing::InitGoogleTest(&argCount, szArgList);

	//testing::InitGoogleTest(__argc, __argv);
	RUN_ALL_TESTS();

	mTestUI->run();
}