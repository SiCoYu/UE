#ifndef __EventDispatchDelegate_H
#define __EventDispatchDelegate_H

//#include "FastDelegate.h"

#include "MySmDelegateCombinations.h"

class IDispatchObject;

//typedef fastdelegate::FastDelegate1<IDispatchObject*> EventDispatchDelegate;
//typedef fastdelegate::FastDelegate1<IDispatchObject*>* EventDispatchDelegatePtr;

//#define MakeEventDispatchDelegate EventDispatchDelegate

DECLARE_DELEGATE_OneParam(EventDispatchDelegate, IDispatchObject*);
typedef EventDispatchDelegate* EventDispatchDelegatePtr;

#define MakeEventDispatchDelegate EventDispatchDelegate().BindRaw

#endif