#include "MyProject.h"
#include "AuxButton.h"
#include "UtilSysLibWrap.h"
#include "MClassFactory.h"

namespace MyNS
{
	M_IMPLEMENT_AND_REGISTER_CLASS(AuxButton, AuxWindow)

	AuxButton::AuxButton()
	{
		this->mNativeButton = nullptr;
		//this->mScriptDelegate = nullptr;
	}

	AuxButton::~AuxButton()
	{

	}

	void AuxButton::init()
	{
		Super::init();
	}

	void AuxButton::dispose()
	{
		Super::dispose();
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