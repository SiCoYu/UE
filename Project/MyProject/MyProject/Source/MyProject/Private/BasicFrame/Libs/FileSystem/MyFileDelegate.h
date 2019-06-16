#ifndef __MyFileDelegate_H
#define __MyFileDelegate_H

#include "TypeDef.h"
#include "PlatformDefine.h"
#include "MySimpleDelegateDef.h"
#include "Containers/UnrealString.h"	// FString

/**
 * @brief MyFileDelegate.h
 */
MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

MY_MINI_DECLARE_DELEGATE_RetVal_ThreeParams(bool, MyTraverseDirectoryDelegate, FString, FString, FString);
typedef MyTraverseDirectoryDelegate* MyTraverseDirectoryDelegatePtr;

#define MakeMyTraverseDirectoryDelegate(pThis,handle,param) MyTraverseDirectoryDelegate().bindObjectHandle(handle, pThis, param)
#define MakeStaticMyTraverseDirectoryDelegate(handle,param) MyTraverseDirectoryDelegate().bindStaticHandle(handle, param)

MY_END_NAMESPACE

#endif