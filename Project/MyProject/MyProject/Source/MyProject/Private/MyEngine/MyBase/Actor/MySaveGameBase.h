#pragma once

#include "GameFramework/SaveGame.h"
#include "MySaveGameBase.generated.h"

/**
 * @url https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Code/index.html
 */

UCLASS()
class UMySaveGameBase : public USaveGame
{
	GENERATED_UCLASS_BODY()

public:
	/** Loads user persistence data if it exists, creates an empty record otherwise. */
	static UMySaveGameBase* LoadPersistentUser(FString SlotName, const int32 UserIndex);

private:
	/** The string identifier used to save/load this persistent user. */
	FString SlotName;
	int32 UserIndex;
};