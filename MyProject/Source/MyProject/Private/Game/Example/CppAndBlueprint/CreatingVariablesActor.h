#pragma once

#include "GameFramework/Actor.h"
#include "CreatingVariablesActor.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Blueprints,_Creating_Variables_in_C%2B%2B_For_Use_In_BP
 */

UCLASS(config = Game)
class ACreatingVariablesActor : public AActor
{
	GENERATED_BODY()

public:
	ACreatingVariablesActor(const FObjectInitializer& ObjectInitializer);

	//Comments that you write as shown will be very neatly and wonderfully shown when the user hovers the mouse over the variable name in the Editor! 
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerMusicSkill)
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerMusicSkill)
	//If you use quotation marks you can create fancier category names! 
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PlayerMusicSkill ~ Yay!")

	/** What is the Player's current musical skill level? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerMusicSkill)
	int32 MusicSkillLevel;
};