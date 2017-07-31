#pragma once

#include "GameFramework/PlayerController.h"
#include "ClearWidgetsPlayerController.generated.h"

/**
* @brief https://wiki.unrealengine.com/Clear_Widgets_When_Switching_Levels
*/

UCLASS()
class AClearWidgetsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable, Category = "Things")
	void ClearHUDWidgets();
	virtual void ClearHUDWidgets_Implementation();
};