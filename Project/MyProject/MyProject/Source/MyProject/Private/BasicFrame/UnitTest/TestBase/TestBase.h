#ifndef __TestBase_H
#define __TestBase_H

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TestBase : public GObject
{
public:
	virtual void run() = 0;

	virtual void init();
	virtual void dispose();
};

MY_END_NAMESPACE

#endif