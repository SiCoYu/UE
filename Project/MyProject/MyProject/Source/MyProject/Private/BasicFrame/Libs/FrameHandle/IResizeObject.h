#ifndef __IResizeObject_H
#define __IResizeObject_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IResizeObject
{
public:
    virtual void onResize(int viewWidth, int viewHeight) = 0;
};

MY_END_NAMESPACE

#endif