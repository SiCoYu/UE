#ifndef __TestBase_H
#define __TestBase_H
#include "GObject.h"

class TestBase : public GObject
{
public:
	virtual void run() = 0;
};

#endif