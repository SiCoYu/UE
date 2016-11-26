#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "AccessMeshActor.generated.h"

/**
* @brief https://wiki.unrealengine.com/Accessing_mesh_triangles_and_vertex_positions_in_build
*/

UCLASS(config = Game)
class AAccessMeshActor : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* MyStaticMesh;

public:
	AAccessMeshActor(const FObjectInitializer& ObjectInitializer);
	void AccessData();
};