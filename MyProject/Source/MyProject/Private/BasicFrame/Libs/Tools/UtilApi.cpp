#include "MyProject.h"
#include "UtilApi.h"

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