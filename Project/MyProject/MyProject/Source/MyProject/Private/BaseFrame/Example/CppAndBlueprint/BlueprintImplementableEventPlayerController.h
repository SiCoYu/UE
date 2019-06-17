#pragma once

#include "GameFramework/PlayerController.h"
#include "BlueprintImplementableEventPlayerController.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Blueprints,_Empower_Your_Entire_Team_With_BlueprintImplementableEvent
 */

UCLASS()
class ABlueprintImplementableEventPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	float Health;

	// Remapping old metadata key 'FriendlyName' to new key 'DisplayName', please update the declaration.
	/** Player's Health is Currently Above 50! Returns
	player's exact current health for convenience. This
	function runs every tick that the player's health
	is high enough! Play healthy sounds here. */
	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "Player Health ~ Player Is Healthy Tick"))
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Player Health ~ Player Is Healthy Tick"))
	void PlayerIsHealthyTick(float CurrentHealth);

	void PlayerTick(float DeltaTime);
};