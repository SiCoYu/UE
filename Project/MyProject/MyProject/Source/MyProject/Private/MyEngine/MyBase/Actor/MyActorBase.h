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
	// ȱ����������๹�챨��error C2664: 'AMyActorBase::AMyActorBase(AMyActorBase &&)': cannot convert argument 1 from 'const FObjectInitializer' to 'FVTableHelper &'
	AMyActorBase(const FObjectInitializer& ObjectInitializer);
	AMyActorBase();
	virtual ~AMyActorBase();

public:
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	void SetInfo(FString name);

	// ue4-����ִ̨�з���: http://blog.csdn.net/yangxuan0261/article/details/53969564
	UFUNCTION(Exec)
	void execInConsole();

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
