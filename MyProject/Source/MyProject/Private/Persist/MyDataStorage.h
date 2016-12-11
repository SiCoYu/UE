#pragma once

#include "MyDataStorage.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Global_Data_Access,_Data_Storage_Class_Accessible_From_Any_CPP_or_BP_Class_During_Runtime!
 Project Settings->Engine->General
 Help My Project Wont Load Any More, Editor Just Crashes

 If your Data Singleton class gets deleted misplaced or renamed in some unusual fashion, you can end up in situation where your project simply will not load!

 There's an easy fix!

 Just navigate to your Config/DefaultEngine.ini and remove the line related to your singleton class which is now missing

 [/Script/Engine.Engine]
 GameViewportClientClassName=/Script/Engine.GameViewportClient
 GameViewportClientClassName=/Script/Solus.SolusViewportClient
 LevelScriptActorClassName=/Script/Engine.LevelScriptActor
 LevelScriptActorClassName=/Script/Solus.SolusLevelScriptActor
 GameSingletonClassName=/Game/Rama/SolusDataSingletonBP.SolusDataSingletonBP_C  ;<-----
 */

UCLASS(Blueprintable, BlueprintType)
class UMyDataStorage : public UObject
{
	GENERATED_BODY()
public:
	UMyDataStorage(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
	TArray<UClass*> SolusTreeBlueprints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
	UTexture2D* SolusT2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
	FVector SolusEssentialVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
	FString SolusCoreFilePath;
};