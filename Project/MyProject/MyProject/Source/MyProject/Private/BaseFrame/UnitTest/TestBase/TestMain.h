#ifndef __TestMain_H
#define __TestMain_H

#include "GObject.h"
#include "PlatformDefine.h"

class TestExtern;

MY_BEGIN_NAMESPACE(MyNS)

class TestSocket;
class TestUi;
class TestDownload;
class TestLuaBind;
class TestPak;

class TestMain : public GObject
{
public:
	TestExtern* mTestExtern;
	TestSocket* mTestSocket;
	TestUi* mTestUi;
	TestDownload* mTestDownload;
	TestLuaBind* mTestLuaBind;
	TestPak* mTestPak;

public:
	TestMain();
	~TestMain();

public:
	void init();
	void dispose();

	void runTest();
};

MY_END_NAMESPACE

#endif				// __TestMain_H