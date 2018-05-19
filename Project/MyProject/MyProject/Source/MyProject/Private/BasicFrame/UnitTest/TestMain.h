#ifndef __TestMain_H
#define __TestMain_H

class TestExtern;
class TestSocket;
class TestUi;
class TestDownload;
class TestLuaBind;

class TestMain
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