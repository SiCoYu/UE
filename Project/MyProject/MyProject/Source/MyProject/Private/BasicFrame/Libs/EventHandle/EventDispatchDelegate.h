#ifndef __EventDispatchDelegate_H
#define __EventDispatchDelegate_H

#include "TypeDef.h"
#include "PlatformDefine.h"
#include "MySimpleDelegateDef.h"

/**
 * @brief EventDispatchDelegate.h
 */
MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

MY_MINI_DECLARE_DELEGATE_OneParam(EventDispatchDelegate, IDispatchObject*);
typedef EventDispatchDelegate* EventDispatchDelegatePtr;

#define MakeEventDispatchDelegate(pThis,handle,param) EventDispatchDelegate().bindObjectHandle(handle, pThis, param)
#define MakeStaticEventDispatchDelegate(handle,param) EventDispatchDelegate().bindStaticHandle(handle, param)

MY_END_NAMESPACE

#endif