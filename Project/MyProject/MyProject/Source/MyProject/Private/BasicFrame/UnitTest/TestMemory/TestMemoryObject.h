#ifndef __TestMemoryObject_H
#define __TestMemoryObject_H

#include "CoreInc.h"

class TestMemoryObject : public GObject
{
	M_DECLARE_CLASS(TestMemoryObject, GObject);

public:
	void test();
};

#endif