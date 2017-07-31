#pragma once

#include "UObject/Interface.h"
#include "ReactsToTimeOfDay.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Interfaces_in_C%2B%2B
 */

/* must have BlueprintType as a specifier to have this interface exposed to blueprints
with this line you can easily add this interface to any blueprint class */
UINTERFACE(BlueprintType)
class UReactsToTimeOfDay : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IReactsToTimeOfDay
{
	GENERATED_IINTERFACE_BODY()

public:
	//classes using this interface must implement ReactToHighNoon
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
	bool ReactToHighNoon();

	//classes using this interface may implement ReactToMidnight
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "MyCategory")
	bool ReactToMidnight();
};