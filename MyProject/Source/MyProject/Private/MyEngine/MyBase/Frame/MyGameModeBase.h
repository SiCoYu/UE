#pragma once

//#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

// AGameModeBase ���ģʽ������� Actor �� BeginPlayer����Ϊ WorldSetting �е� BeginPlyer
UCLASS(minimalapi)
//class AMyGameModeBase : public AGameModeBase
class AMyGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
	AMyGameModeBase(const FObjectInitializer& ObjectInitializer);

	// ue4-����ִ̨�з���: http://blog.csdn.net/yangxuan0261/article/details/53969564
public:
	UFUNCTION(Exec)
	virtual void execInConsole(FString _str, int32 _num);
};