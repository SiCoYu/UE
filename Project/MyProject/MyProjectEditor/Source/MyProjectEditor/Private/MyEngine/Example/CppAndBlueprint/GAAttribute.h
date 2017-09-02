#pragma once

#include "UObject/NameTypes.h"	// FName
#include "SlateCore.h"
#include "GAAttribute.generated.h"

/**
 * @brief https://wiki.unrealengine.com/How_To_Create_Custom_Blueprint_Pin
 First you will need Editor module in your plugin/game project. You can find information how to add it here:

 https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 */

USTRUCT(BlueprintType)
struct FGAAttribute
{
	GENERATED_USTRUCT_BODY()
public:
	// UE4 4.17 : Error: An explicit Category specifier is required for any property exposed to the editor or Blueprints in an Engine module.
	//It's important to mark property as UPROPERTY(), it doesn't need to have any specifiers though.
	//UPROPERTY(BlueprintReadOnly)
	UPROPERTY()
	FName AttributeName;
};