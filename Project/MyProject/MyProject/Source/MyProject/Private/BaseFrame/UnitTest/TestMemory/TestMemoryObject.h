#ifndef __TestMemoryObject_H
#define __TestMemoryObject_H

#include "CoreInc.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestMemoryObject : public GObject
{
	M_DECLARE_CLASS(TestMemoryObject, GObject);

public:
	void test();
};

MY_END_NAMESPACE

#endif