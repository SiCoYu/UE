#pragma once

#include "Engine/LevelScriptActor.h"
#include "Engine/EngineTypes.h"
#include "MyLevelScriptActorBase.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
 */

UCLASS()
class AMyLevelScriptActorBase : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()

	/** A Custom name for each Solus Level, specified in Level BP Default Properties! */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SolusLevel)
	FName SolusLevelName;

	//===========
	// BP Nodes
	//===========
public:
	/** This triggers a save / update of all the Solus Save Game level data. This should be called before the level is unloaded/unstreamed via blueprints.*/
	UFUNCTION(BlueprintCallable, Category = "Solus Level Save System")
	void SolusLevel__UpdateLevelSaveData();

	//OVERRIDES
protected:
	//virtual void ReceiveBeginPlay() override;
	// ALevelScriptActor 父类没有这个函数
	virtual void ReceiveBeginPlay();

	//ON REMOVE FROM WORLD - USE INSTEAD OF BEGIN DESTROY
	/** Called when this actor is in a level which is being removed from the world (e.g. my level is getting UWorld::RemoveFromWorld called on it) */
	/*
	virtual void OnRemoveFromWorld() override;
	*/
	//THIS GOT REPLACED BY
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//TICK
protected:
	//Tick
	virtual void Tick(float DeltaSeconds) override;
};