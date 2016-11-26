#pragma once

#include "MyProject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AccessMeshBPFunctionLibrary.generated.h"

/**
 * @brief ²Î¿¼ UDataTableFunctionLibrary
 */

UCLASS()
class UAccessMeshBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	bool GetStaticMeshVertexLocations(UStaticMeshComponent* Comp, TArray<FVector>& VertexPositions);
};