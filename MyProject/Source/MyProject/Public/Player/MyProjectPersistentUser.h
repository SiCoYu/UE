#pragma once
#include "MyProjectPersistentUser.generated.h"

UCLASS()
class UMyProjectPersistentUser : public USaveGame
{
	GENERATED_UCLASS_BODY()

public:
	/** Loads user persistence data if it exists, creates an empty record otherwise. */
	static UMyProjectPersistentUser* LoadPersistentUser(FString SlotName, const int32 UserIndex);

private:
	/** The string identifier used to save/load this persistent user. */
	FString SlotName;
	int32 UserIndex;
};