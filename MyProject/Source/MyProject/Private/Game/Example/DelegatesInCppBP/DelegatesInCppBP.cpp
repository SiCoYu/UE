#include "MyProject.h"
#include "DelegatesInCppBP.h"
#include "Delegates/Delegate.h"

ADelegatesInCppBP::ADelegatesInCppBP(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void ADelegatesInCppBP::Bind()
{
	//this->RamaMeleeWeapon_OnHit.BindUObject(this, &USomeClass::RespondToMeleeDamageTaken); //see above in wiki

	//this->RamaMeleeWeapon_OnHit.BindRaw(this, &FSomeRawCPPClass::RespondToMeleeDamageTaken);

	//this->RamaMeleeWeapon_OnHit.CreateSP(this, &SSomeSlateClass::RespondToMeleeDamageTaken);
}

void ADelegatesInCppBP::Exec()
{
	//Only the code that is supposed to initiate the event calls Broadcast()
	if (RamaMeleeWeapon_OnHit.IsBound()) //<~~~~
	{
		//RamaMeleeWeapon_OnHit.Broadcast(Hit.GetActor(), Hit.GetComponent(), Hit.ImpactPoint, Hit.ImpactNormal, Hit.BoneName, Hit);
	}
}

void ADelegatesInCppBP::RespondToMeleeDamageTaken(AActor* HitActor, UPrimitiveComponent* HitComponent, const FVector& ImpactPoint, const FVector& ImpactNormal, FName HitBoneName, const FHitResult& HitResult)
{

}