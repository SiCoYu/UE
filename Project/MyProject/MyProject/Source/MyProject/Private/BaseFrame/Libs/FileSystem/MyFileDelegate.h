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

#define MAKE_TRAVERSE_DIRECTORY_DELEGATE(pThis,handle) MyTraverseDirectoryDelegate().bindObjectHandle(handle, pThis)
#define MAKE_STATIC_TRAVERSE_DIRECTORY_DELEGATE(handle) MyTraverseDirectoryDelegate().bindStaticHandle(handle)

MY_END_NAMESPACE

#endif