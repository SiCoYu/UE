#ifndef __TEST_H
#define __TEST_H

class TestExtern;
class TestSocket;

class Test
{
public:
	TestExtern* mTestExtern;
	TestSocket* mTestSocket;

public:
	Test();
	void runTest();
};

#endif				// __TEST_H