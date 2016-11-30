#pragma once

#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerController.h"
#include "Containers/UnrealString.h"
#include "ClearWidgetsPlayerController.h"
#include "ClearWidgetsGameMode.generated.h"

/**
* @brief https://wiki.unrealengine.com/Clear_Widgets_When_Switching_Levels
*/

UCLASS()
class AClearWidgetsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual APlayerController* ProcessClientTravel(FString& FURL, FGuid NextMapGuid, bool bSeamless, bool bAbsolute) override;
};