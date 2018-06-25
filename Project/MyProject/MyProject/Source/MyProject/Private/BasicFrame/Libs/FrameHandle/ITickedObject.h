#ifndef __ITickedObject_H
#define __ITickedObject_H

#include "TickMode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 为了减少虚函数表的数量，接口都统一写在 GObject
 */
class ITickedObject
{
public:
    // virtual void onTick(float delta, TickMode tickMode) = 0;
};

MY_END_NAMESPACE

#endif