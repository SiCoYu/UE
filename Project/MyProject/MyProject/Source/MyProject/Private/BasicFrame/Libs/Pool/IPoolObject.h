#ifndef __IPoolObject_H
#define __IPoolObject_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IPoolObject
{
public:
    virtual void resetDefault() = 0;
};

MY_END_NAMESPACE

#endif