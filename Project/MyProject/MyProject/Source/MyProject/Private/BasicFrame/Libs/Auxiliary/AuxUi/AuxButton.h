#pragma once

#include "AuxWindow.h"
#include "UObject/ScriptDelegates.h"	// TScriptDelegate
#include "UObject/WeakObjectPtr.h"	// FWeakObjectPtr
#include "UObject/Object.h"		// UObject
#include "Blueprint/UserWidget.h"	// UUserWidget

class UButton;

namespace MyNS
{
	class AuxButton : public AuxWindow
	{
	protected:
		UButton* mNativeButton;
		TScriptDelegate<FWeakObjectPtr> mScriptDelegate;

	public:
		AuxButton();
		~AuxButton();

	public:
		TScriptDelegate<FWeakObjectPtr> addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName);
	};
}