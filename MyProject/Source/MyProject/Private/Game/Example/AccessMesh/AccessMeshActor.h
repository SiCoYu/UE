#pragma once

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "AccessMeshActor.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Accessing_mesh_triangles_and_vertex_positions_in_build
 * @brief If you are wondering how to access triangles and vertex positions in packaged project. Here is the solution I found. Accessing this data from Unreal's variables (ex. StaticMesh->GetPhysicsTriMeshData()) will not work since all vertex data of a mesh is serialized when packaging the project. 
 * @brief There is also way of accessing all meshes (welded) of an actor. It can be done by calling GetAllShapes() in BodyInstance. 
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