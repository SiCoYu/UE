#pragma once

#include "UObject/NameTypes.h"	// FName
#include "UObject/ScriptDelegates.h"	// TScriptDelegate
#include "UObject/WeakObjectPtr.h"	// FWeakObjectPtr
#include "Math/Vector.h"	// FVector
#include "GameFramework/Actor.h"	// AActor
#include "UObject/Object.h"		// UObject
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "PlatformDefine.h"

class UUserWidget;
class UObject;

MY_BEGIN_NAMESPACE(MyNS)

class UtilSysLibWrap
{
public:
	static FVector FAKE_POS;

public:
	static TScriptDelegate<FWeakObjectPtr> addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName);

	static void Destroy(AActor* actor, bool bNetForce = false, bool bShouldModifyLevel = true);
	static void DestroyImmediate(AActor* actor, bool bNetForce = false, bool bShouldModifyLevel = true);
};

#include "UtilSysLibWrap.inl"

MY_END_NAMESPACE