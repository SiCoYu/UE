#ifndef __TestMain_H
#define __TestMain_H

class TestExtern;
class TestSocket;
class TestUI;
class TestDownload;

class TestMain
{
public:
	TestExtern* mTestExtern;
	TestSocket* mTestSocket;
	TestUI* mTestUI;
	TestDownload* mTestDownload;

public:
	TestMain();
	void runTest();
};

#endif				// __TestMain_H