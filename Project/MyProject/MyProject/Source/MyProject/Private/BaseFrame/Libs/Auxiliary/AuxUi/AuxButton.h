#pragma once

#include "AuxWindow.h"
#include "UObject/ScriptDelegates.h"	// TScriptDelegate
#include "UObject/WeakObjectPtr.h"	// FWeakObjectPtr
#include "UObject/Object.h"		// UObject
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "PlatformDefine.h"

class UButton;

MY_BEGIN_NAMESPACE(MyNS)

class AuxButton : public AuxWindow
{
	M_DECLARE_CLASS(AuxButton, AuxWindow)

protected:
	UButton* mNativeButton;
	TScriptDelegate<FWeakObjectPtr> mScriptDelegate;

public:
	AuxButton();
	~AuxButton();

public:
	virtual void init() override;
	virtual void dispose() override;

	TScriptDelegate<FWeakObjectPtr> addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName);
};

MY_END_NAMESPACE