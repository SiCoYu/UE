#ifndef __TestMain_H
#define __TestMain_H

class TestExtern;
class TestSocket;
class TestUI;

class TestMain
{
public:
	TestExtern* mTestExtern;
	TestSocket* mTestSocket;
	TestUI* mTestUI;

public:
	Test();
	void runTest();
};

#endif				// __TestMain_H