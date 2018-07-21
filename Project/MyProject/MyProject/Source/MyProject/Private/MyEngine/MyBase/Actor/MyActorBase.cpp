#include "MyProject.h"
#include "MyActorBase.h"
#include "LogCategoryDef.h"

AMyActorBase::AMyActorBase()
{
	
}

AMyActorBase::~AMyActorBase()
{

}

void AMyActorBase::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
}

void AMyActorBase::SetInfo(FString name)
{
	this->mName = name;
}

void AMyActorBase::execInConsole()
{
	UE_LOG(ComWarning, Warning, TEXT("name:%s, Say hello"), *mName);
}

void AMyActorBase::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}