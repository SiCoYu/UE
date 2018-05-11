#ifndef __EventDispatchDelegate_H
#define __EventDispatchDelegate_H

//#include "FastDelegate.h"

/**
 * @url https://github.com/marcmo/delegates
 */
#include "MiniClosure.h"
#include "MiniDelegate.h"

class IDispatchObject;

//typedef fastdelegate::FastDelegate1<IDispatchObject*> EventDispatchDelegate;
//typedef fastdelegate::FastDelegate1<IDispatchObject*>* EventDispatchDelegatePtr;

//#define MakeEventDispatchDelegate EventDispatchDelegate

typedef dlgt::delegate<IDispatchObject*> EventDispatchDelegate;
typedef dlgt::delegate<IDispatchObject*>* EventDispatchDelegatePtr;

#define MakeEventDispatchDelegate make_delegate

#endif