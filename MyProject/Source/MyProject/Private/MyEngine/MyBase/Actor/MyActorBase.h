#pragma once

#include "GameFramework/Actor.h"
#include "MyActorBase.generated.h"

UCLASS(config=Game)
class AMyActorBase : public AActor
{
	GENERATED_BODY()

private:
	FString mName;

public:
	AMyActorBase();
	virtual ~AMyActorBase();

public:
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	void SetInfo(FString name);

	// ue4-控制台执行方法: http://blog.csdn.net/yangxuan0261/article/details/53969564
	UFUNCTION(Exec)
	void execInConsole();
};
