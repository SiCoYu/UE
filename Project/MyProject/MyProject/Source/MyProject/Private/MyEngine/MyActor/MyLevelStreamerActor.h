#pragma once

#include "MyActorBase.h"
#include "MyLevelStreamerActor.generated.h"

/**
* @brief Load and Unload Levels with C++£º http://docs.unrealengine.com/latest/INT/Engine/LevelStreaming/HowTo/StreamWithC++/index.html
*/

UCLASS(config = Game)
class AMyLevelStreamerActor : public AMyActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyLevelStreamerActor();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere)
	FName LevelToLoad;

private:
	// Overlap volume to trigger level streaming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverlapVolume;
};