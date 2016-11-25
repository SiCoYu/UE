#pragma once

#include "MyProject.h"
#include "Delegates/DelegateCombinations.h"
#include "DelegatesInCppBP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FRamaMeleeHitSignature, class AActor*, HitActor, class UPrimitiveComponent*, HitComponent, const FVector&, ImpactPoint, const FVector&, ImpactNormal, FName, HitBoneName, const struct FHitResult&, HitResult);

/**
* @brief https://wiki.unrealengine.com/Delegates_In_UE4,_Raw_Cpp_and_BP_Exposed
*/

UCLASS(config = Game)
class ADelegatesInCppBP : public AActor
{
	GENERATED_BODY()

public:
	ADelegatesInCppBP(const FObjectInitializer& ObjectInitializer);

	//This should be in the class which calls the delegate, and where the signature was defined
	//This is an instance of the signature that was defined above!
	FRamaMeleeHitSignature RamaMeleeWeapon_OnHit;

	void Bind();
	void Exec();

	// If your delegate Broadcast stalls the game for a bit and then doesnt work, it's because you did not make one of your receiving functions a UFUNCTION() 
	//Any class can add a function that uses the delegate signature and responds to the Broadcast() event 
	UFUNCTION()
	void RespondToMeleeDamageTaken(AActor* HitActor, UPrimitiveComponent* HitComponent, const FVector& ImpactPoint, const FVector& ImpactNormal, FName HitBoneName, const FHitResult& HitResult);

	// A BP friendly delegate requires this additional .h code to expose the delegate to Blueprints. 
	// BP-friendly Delegates should be DYNAMIC_MULTICAST so they can be serialized (saved/loaded) with the BP graph. 
	// When you've made BP-friendly delegates on objects that you can place in the level, you can simply right click on the object instance in your level -> Add Event and see your new delegate! So nice! 
	//UPROPERTY(BlueprintAssignable, Category = "Rama Melee Weapon")
	//FRamaMeleeHitSignature RamaMeleeWeapon_OnHit;
};