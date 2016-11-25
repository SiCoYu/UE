#pragma once

#include "UObject/ScriptInterface.h"
#include "CppAndBlueprintTargetInterface.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Expose_an_interface_to_blueprint
 * @brief C++ µ÷ÓÃ Blueprint
 */

UINTERFACE(MinimalAPI)
class UCppAndBlueprintTargetInterface :
	public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICppAndBlueprintTargetInterface {
	GENERATED_IINTERFACE_BODY()

public:
	// Remapping old metadata key 'FriendlyName' to new key 'DisplayName', please update the declaration.
	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "On Interact"))
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interact"))
	void OnInteract(const TScriptInterface<ICppAndBlueprintTargetInterface> &clicked);
	virtual float GetHealth();
};