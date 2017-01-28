#include "MyProject.h"
#include "AuxButton.h"
#include "UtilApi.h"

namespace MyNS
{
	AuxButton::AuxButton()
	{
		this->mNativeButton = nullptr;
		//this->mScriptDelegate = nullptr;
	}

	AuxButton::~AuxButton()
	{

	}

	TScriptDelegate<FWeakObjectPtr> AuxButton::addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName)
	{
		if (nullptr != widget && nullptr != pThis)
		{
			this->mNativeButton = Cast<UButton>(widget->GetWidgetFromName(buttonName));
			if (nullptr != this->mNativeButton)
			{
				this->mScriptDelegate.BindUFunction(pThis, functionName);
				this->mNativeButton->OnClicked.Add(this->mScriptDelegate);
			}
		}

		return this->mScriptDelegate;
	}
}