#ifndef __TestMain_H
#define __TestMain_H

#include "GObject.h"

class TestExtern;
class TestSocket;
class TestUi;
class TestDownload;
class TestLuaBind;

class TestMain : public GObject
{
public:
	TestExtern* mTestExtern;
	TestSocket* mTestSocket;
	TestUi* mTestUI;
	TestDownload* mTestDownload;
	TestLuaBind* mTestLuaBind;

public:
	TestMain();
	~TestMain();

public:
	void init();
	void dispose();

	void runTest();
};

#endif				// __TestMain_H