#pragma once

#include "MyProject.h"
#include "PlayerPawnData.h"
#include "MyPawn.h"
#include "MyPlayerController.generated.h"

/**
 APlayerController BeginPlayer 就说明可以运行了
 逻辑控制基本获取 APlayerController就行了，不用必须在 Actor 中处理
 */

class UUserWidget;

//UCLASS(Within=Engine, transient, config=Engine)
UCLASS(config = Game)
class AMyPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	//public:
	//	AMyPlayerController(const FObjectInitializer& ObjectInitializer)

protected:
	/* Use BeginPlay to start the functionality */
	virtual void BeginPlay() override;
	virtual void ReceivedPlayer() override;

protected:
	void TestUI();

	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Every_Player
public:
	PlayerPawnData CurrentPawnData;

	// https://wiki.unrealengine.com/Spawn_Different_Pawns_For_Players_in_Multiplayer
public:
	FORCEINLINE UClass* GetPlayerPawnClass() { return MyPawnClass; }

protected:
	void BeginPlay_PawnClass();

	/* Return The Correct Pawn Class Client-Side */
	UFUNCTION(Reliable, Client)
	void DeterminePawnClass();
	//virtual void DeterminePawnClass_Implementation();

	/* Set Pawn Class On Server For This Controller */
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerSetPawn(TSubclassOf<APawn> InPawnClass);
	//virtual void ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass);
	//virtual bool ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass);

	/* Actual Pawn class we want to use */
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;

	/* First Pawn Type To Use */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	//TSubclassOf<AGESGame_ServerPawn> PawnToUseA;
	TSubclassOf<AMyPawn> PawnToUseA;

	/* Second Pawn Type To Use */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "My Controller")
	//TSubclassOf<AGESGame_Pawn> PawnToUseB;
	TSubclassOf<AMyPawn> PawnToUseB;

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

	// https://wiki.unrealengine.com/UMG,_Referencing_UMG_Widgets_in_Code
public:
	void BeginPlay_UMGWidgets();

	// Note: that am using forward declaration Because am not including the
	// widget in the header and to prevent circular dependency.
	// you dont need to do that if you include the Widget Class in the .h
	// forward declaration is just putting "class" before the class name so the compiler know its a
	// class but its not included in the header and don't freak out. Ex. “class UUserWidget”

	// Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wMainMenu;

	// Variable to hold the widget After Creating it.
	UUserWidget* MyMainMenu;
};