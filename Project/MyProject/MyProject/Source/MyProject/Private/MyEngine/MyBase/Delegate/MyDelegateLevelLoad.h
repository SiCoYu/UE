#pragma once

#include "MyDelegateBase.h"	// UMyDelegateBase
#include "MyDelegateLevelLoad.generated.h"

/**
 * @brief Delegate
 */

UCLASS()
class UMyDelegateLevelLoad : public UMyDelegateBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyDelegateLevelLoad")
	void onLevelLoaded();
};