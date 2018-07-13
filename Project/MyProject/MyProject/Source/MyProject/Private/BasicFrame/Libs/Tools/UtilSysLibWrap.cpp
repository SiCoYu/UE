#include "MyProject.h"
#include "UtilSysLibWrap.h"
#include <ctime>

MY_BEGIN_NAMESPACE(MyNS)

FVector UtilSysLibWrap::FAKE_POS = FVector(-1000, 0, -1000);

TScriptDelegate<FWeakObjectPtr> UtilSysLibWrap::addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName)
{
	TScriptDelegate<FWeakObjectPtr> handle;

	if (nullptr != widget && nullptr != pThis)
	{
		//UButton* button = widget->GetSlateWidgetFromName(buttonName);
		UButton* button = Cast<UButton>(widget->GetWidgetFromName(buttonName));
		if (nullptr != button)
		{
			handle.BindUFunction(pThis, functionName);
			button->OnClicked.Add(handle);
		}
	}

	return handle;
}

void UtilSysLibWrap::Destroy(AActor* actor, bool bNetForce, bool bShouldModifyLevel)
{
	if (nullptr != actor)
	{
		actor->Destroy(bNetForce, bShouldModifyLevel);
	}
}

void UtilSysLibWrap::DestroyImmediate(AActor* actor, bool bNetForce, bool bShouldModifyLevel)
{
	if (nullptr != actor)
	{
		actor->Destroy(bNetForce, bShouldModifyLevel);
	}
}

std::string UtilSysLibWrap::getRandomVersion()
{
	std::string ret = "";

	ret = ctime(time(NULL));

	return ret;
}

MY_END_NAMESPACE