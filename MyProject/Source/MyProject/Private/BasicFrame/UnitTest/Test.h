#ifndef __Test_H
#define __Test_H

class TestExtern;
class TestSocket;
class TestUI;

class Test
{
public:
	TestExtern* mTestExtern;
	TestSocket* mTestSocket;
	TestUI* mTestUI;

public:
	Test();
	void runTest();
};

#endif				// __TEST_H