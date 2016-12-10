#pragma once

#include "MyProject.h"
#include "PlayerPawnData.h"
#include "MyPawn.h"
#include "MyProjectPlayerController.generated.h"

UCLASS(Within=Engine, transient, config=Engine)
class AMyProjectPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	//public:
	//	AMyProjectPlayerController(const FObjectInitializer& ObjectInitializer)

	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Every_Player
public:
	PlayerPawnData CurrentPawnData;

	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Players_in_Multiplayer
public:
	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }

protected:
	/* Return The Correct Pawn Class Client-Side */
	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
	virtual void DeterminePawnClass_Implementation();

	/* Use BeginPlay to start the functionality */
	virtual void BeginPlay() override;

	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
	virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);

	/* Actual Pawn class we want to use */
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;

	/* First Pawn Type To Use */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	//TSubclassOf<AGESGame_ServerPawn> PawnToUseA;
	TSubclassOf<MyPawnActor> PawnToUseA;

	/* Second Pawn Type To Use */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	//TSubclassOf<AGESGame_Pawn> PawnToUseB;
	TSubclassOf<MyPawnActor> PawnToUseB;

	// https://wiki.unrealengine.com/Streamed_Levels,_Test_If_Actor_Is_In_Level_Bounds
public:
	bool IsActorWithinTheBoundsOfStreamedInLeve();


	// https://wiki.unrealengine.com/Timer_Macros
protected:
	FTimerHandle TimerHandle_Taunt;
	float LastTauntTime;

	UFUNCTION()
	void TauntTimer();

	void ServerTaunt_Implementation();


	// https://wiki.unrealengine.com/Trace_Functions
public:
	void ExampleUsageOne();
	void ExampleUsageTwo();
	void ExampleUsageThree();
	void ExampleUsageFour();
};