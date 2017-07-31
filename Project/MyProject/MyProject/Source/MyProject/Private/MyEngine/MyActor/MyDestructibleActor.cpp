#include "MyProject.h"
#include "MyDestructibleActor.h"

AMyDestructibleActor::AMyDestructibleActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

//Tick
void AMyDestructibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//~~~~~~~~~~~~

	//Draw All Centers to the screen!
#if WITH_PHYSX
	ScreenMsg("Got into PhysX!!!");

	//4.8 Version
	//'ADestructibleActor::DestructibleComponent': DestructibleComponent should not be accessed directly, please use GetDestructibleComponent() function instead.DestructibleComponent will soon be private and your code will not compile.Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//uint32 ChunkCount = DestructibleComponent->ApexDestructibleActor->getNumVisibleChunks();
	//const uint16* ChunkIndices = DestructibleComponent->ApexDestructibleActor->getVisibleChunks();
	uint32 ChunkCount = GetDestructibleComponent()->ApexDestructibleActor->getNumVisibleChunks();
	const uint16* ChunkIndices = GetDestructibleComponent()->ApexDestructibleActor->getVisibleChunks();
	for (uint32 c = 0; c < ChunkCount; c++)
	{
		//PxRigidDynamic* PActor = DestructibleComponent->ApexDestructibleActor->getChunkPhysXActor(ChunkIndices[c]);
		PxRigidDynamic* PActor = GetDestructibleComponent()->ApexDestructibleActor->getChunkPhysXActor(ChunkIndices[c]);
		check(PActor);
		PxTransform Trans = PActor->getGlobalPose();
		PxVec3& PxLoc = Trans.p;

		FVector Location(PxLoc.x, PxLoc.y, PxLoc.z);

		DrawPoint(Location);

		ScreenMsg("physx loc", Location.ToString());
	}

	/* PRE 4.8 Version
	for(FDestructibleChunkInfo& Each : DestructibleComponent->ChunkInfos)
	{
	physx::PxRigidDynamic* Actor = Each.Actor;

	if(Actor)
	{
	PxTransform Trans = Actor->getGlobalPose();
	PxVec3& PxLoc = Trans.p;

	FVector Location(PxLoc.x,PxLoc.y,PxLoc.z);

	DrawPoint(Location);

	ScreenMsg("physx loc", Location.ToString());
	}
	}
	*/
#endif // WITH_PHYSX 
}