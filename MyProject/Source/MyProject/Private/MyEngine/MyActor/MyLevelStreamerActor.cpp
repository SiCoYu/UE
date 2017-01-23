#include "MyProject.h"
#include "MyLevelStreamerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyLevelStreamerActor::AMyLevelStreamerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;

	OverlapVolume->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyLevelStreamerActor::OverlapBegins);
}

// Called when the game starts or when spawned
void AMyLevelStreamerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyLevelStreamerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyLevelStreamerActor::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == MyCharacter && LevelToLoad != "")
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
	}
}