#pragma once

#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// AGameModeBase ���ģʽ������� Actor �� BeginPlayer����Ϊ WorldSetting �е� BeginPlyer
UCLASS(minimalapi)
class AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
};



