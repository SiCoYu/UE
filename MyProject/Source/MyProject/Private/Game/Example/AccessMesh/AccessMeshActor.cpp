#include "MyProject.h"

#include "PhysicsPublic.h"
#include "PhysXIncludes.h"
#include "ThirdParty/PhysX/PhysX_3.4/Include/geometry/PxTriangleMesh.h"
//#include "ThirdParty/PhysX/PhysX_3.4/Include/foundation/PxSimpleTypes.h"

#include "AccessMeshActor.h"

AAccessMeshActor::AAccessMeshActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

void AAccessMeshActor::AccessData()
{
	MyStaticMesh = Cast<UStaticMeshComponent>(this->GetComponentsByClass(UStaticMeshComponent::StaticClass()));

	// MyStaticMesh is a UStaticMeshComponent
	PxTriangleMesh* TempTriMesh = MyStaticMesh->BodyInstance.BodySetup.Get()->TriMesh;

	check(TempTriMesh);
	int32 TriNumber = TempTriMesh->getNbTriangles();

	const PxVec3* PVertices = TempTriMesh->getVertices();
	const void* Triangles = TempTriMesh->getTriangles();

	// Grab triangle indices
	int32 I0, I1, I2;

	for (int32 TriIndex = 0; TriIndex < TriNumber; ++TriIndex)
	{
		if (TempTriMesh->getTriangleMeshFlags() & PxTriangleMeshFlag::eHAS_16BIT_TRIANGLE_INDICES)
		{
			PxU16* P16BitIndices = (PxU16*)Triangles;
			I0 = P16BitIndices[(TriIndex * 3) + 0];
			I1 = P16BitIndices[(TriIndex * 3) + 1];
			I2 = P16BitIndices[(TriIndex * 3) + 2];
		}
		else
		{
			PxU32* P32BitIndices = (PxU32*)Triangles;
			I0 = P32BitIndices[(TriIndex * 3) + 0];
			I1 = P32BitIndices[(TriIndex * 3) + 1];
			I2 = P32BitIndices[(TriIndex * 3) + 2];
		}

		// Local position
		const FVector V0 = P2UVector(PVertices[I0]);
		const FVector V1 = P2UVector(PVertices[I1]);
		const FVector V2 = P2UVector(PVertices[I2]);
	}
}