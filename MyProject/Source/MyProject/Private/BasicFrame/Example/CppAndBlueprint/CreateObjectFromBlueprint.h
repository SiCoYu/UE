//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CreateObjectFromBlueprint.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Blueprint_Node:_Create_Object_from_Blueprint
 * @brief https://wiki.unrealengine.com/Garbage_Collection_%26_Dynamic_Memory_Allocation
 */

UCLASS()
class UCreateObjectFromBlueprint : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
	static UObject* NewObjectFromBlueprint(UObject* WorldContextObject, UClass* UC);
};