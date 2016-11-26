#include "MyProject.h"

#include "PhysicsPublic.h"
#include "PhysXIncludes.h"
#include "ThirdParty/PhysX/PhysX_3.4/Include/geometry/PxTriangleMesh.h"
//#include "ThirdParty/PhysX/PhysX_3.4/Include/foundation/PxSimpleTypes.h"

#include "AccessMeshBPFunctionLibrary.h"

UAccessMeshBPFunctionLibrary::UAccessMeshBPFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//Get Transformed Vertex positions of any static mesh! -Rama
bool UAccessMeshBPFunctionLibrary::GetStaticMeshVertexLocations(UStaticMeshComponent* Comp, TArray<FVector>& VertexPositions)
{
	//if (!Comp)
	//{
	//	return false;
	//}

	//if (!Comp->IsValidLowLevel())
	//{
	//	return false;
	//}
	////~~~~~~~~~~~~~~~~~~~~~~~

	////Component Transform
	//FTransform RV_Transform = Comp->GetComponentTransform();

	////Body Setup valid?
	//UBodySetup* BodySetup = Comp->GetBodySetup();

	//if (!BodySetup || !BodySetup->IsValidLowLevel())
	//{
	//	return false;
	//}

	////array as of 4.9
	//for (PxTriangleMesh* EachTriMesh : BodySetup->TriMeshes)
	//{
	//	if (!EachTriMesh)
	//	{
	//		return false;
	//	}
	//	//~~~~~~~~~~~~~~~~

	//	//Number of vertices
	//	PxU32 VertexCount = EachTriMesh->getNbVertices();

	//	//Vertex array
	//	const PxVec3* Vertices = EachTriMesh->getVertices();

	//	//For each vertex, transform the position to match the component Transform 
	//	for (PxU32 v = 0; v < VertexCount; v++)
	//	{
	//		VertexPositions.Add(RV_Transform.TransformPosition(P2UVector(Vertices[v])));
	//	}
	//}

	return true;
}