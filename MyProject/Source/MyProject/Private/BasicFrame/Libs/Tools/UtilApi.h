#pragma once

#include "UObject/NameTypes.h"	// FName
#include "UObject/ScriptDelegates.h"	// TScriptDelegate
#include "UObject/WeakObjectPtr.h"	// FWeakObjectPtr
#include "Math/Vector.h"	// FVector

class UUserWidget;
class UObject;

class UtilApi
{
public:
	static FVector FAKE_POS;

public:
	static TScriptDelegate<FWeakObjectPtr> addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName);
};