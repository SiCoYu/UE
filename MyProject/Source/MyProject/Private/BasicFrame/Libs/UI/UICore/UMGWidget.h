#pragma once

#include "Blueprint/UserWidget.h"	// UUserWidget
#include "Templates/SubclassOf.h"		// TSubclassOf
#include "UMGWidget.generated.h"

UCLASS(config=Game)
class UUMGWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TSubclassOf<class UUserWidget>  WidgetClass;
};