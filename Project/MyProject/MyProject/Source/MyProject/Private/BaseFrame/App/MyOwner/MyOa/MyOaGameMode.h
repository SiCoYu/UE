#pragma once

#include "MyGameModeBase.h"	// AGameModeBase
#include "GameFramework/GameMode.h"	// AGameModeBase
#include "MyOaGameMode.generated.h"

// minimalapi ������ Windows �� ���� dll ����
//UCLASS(minimalapi)
class AMyOaGameMode : public AMyGameModeBase
{
	GENERATED_BODY()
};