#include "ObjectIterators.h"
#include "UObject/UObjectIterator.h"
#include "EngineUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMeshActor.h"

void ObjectIterators::IteratorAllComponent()
{
	for (TObjectIterator<USkeletalMeshComponent> Itr; Itr; ++Itr)
	{
		USkeletalMeshCompoment *Component = *Itr;
	}
}

void ObjectIterators::IteratorAllComponent()
{
	for (TActorIterator<AStaticMeshActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AStaticMeshActor *Mesh = *ActorItr;
	}
}

//Object Iterator & Actor Iterator Comparison
//Because AActor extends UObject, the Object Iterator can search for AActors while the Actor Iterator cannot search for instances of UObjects that do not extend AActor at some point.Thus the Object Iterator can search for all UStaticMeshComponents as well as all ACharacters :
//TObjectIterator<UStaticMeshComponent> Itr;
//TObjectIterator<ACharacter> Itr;


//As noted above the Actor Iterator is a special case Object Iterator.Given a UWorld* context it saves you checking the world of the actors as one would need to when using the Object Iterator directly :
//TActorIterator ActorItr<AStaticMeshActor>(GetWorld());