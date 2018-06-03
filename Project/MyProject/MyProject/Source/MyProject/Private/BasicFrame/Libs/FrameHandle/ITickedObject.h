#ifndef __ITickedObject_H
#define __ITickedObject_H

#include "TickMode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ITickedObject
{
public:
    virtual void onTick(float delta, TickMode tickMode) = 0;
};

MY_END_NAMESPACE

#endif