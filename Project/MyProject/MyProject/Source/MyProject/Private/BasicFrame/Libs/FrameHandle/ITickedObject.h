#ifndef __ITickedObject_H
#define __ITickedObject_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ITickedObject
{
public:
    virtual void onTick(float delta) = 0;
};

MY_END_NAMESPACE

#endif