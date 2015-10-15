#ifndef __EventDispatchDelegate_H
#define __EventDispatchDelegate_H

#include "FastDelegate.h"

class IDispatchObject;

typedef fastdelegate::FastDelegate1<IDispatchObject*> EventDispatchDelegate;
typedef fastdelegate::FastDelegate1<IDispatchObject*>* EventDispatchDelegatePtr;

#endif