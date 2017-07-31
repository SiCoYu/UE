#include "MyProject.h"
#include "UtilApi.h"

FVector UtilApi::FAKE_POS = FVector(-1000, 0, -1000);

TScriptDelegate<FWeakObjectPtr> UtilApi::addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName)
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

void UtilApi::Destroy(AActor* actor, bool bNetForce, bool bShouldModifyLevel)
{
	if (nullptr != actor)
	{
		actor->Destroy(bNetForce, bShouldModifyLevel);
	}
}

void UtilApi::DestroyImmediate(AActor* actor, bool bNetForce, bool bShouldModifyLevel)
{
	if (nullptr != actor)
	{
		actor->Destroy(bNetForce, bShouldModifyLevel);
	}
}