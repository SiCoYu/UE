#pragma once

#include "GameFramework/Actor.h"
#include "CppAndBlueprintTargetInterface.h"
#include "UObject/ScriptInterface.h"
#include "TargetInterfaceBPFunctionLibrary.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Expose_an_interface_to_blueprint
 * @brief Blueprint µ÷ÓÃ C++
 */

UCLASS()
class UTargetInterfaceBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "TargetInterface")
	static float GetHealth(const TScriptInterface<ICppAndBlueprintTargetInterface> &target);
};