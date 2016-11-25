#include "MyProject.h"
#include "RWConfigFilePlayerController.h"

//ARWConfigFilePlayerController::ARWConfigFilePlayerController(const class FObjectInitializer& PCIP)
//	: Super(PCIP)
//{
//
//}

//in your player controller class
void ARWConfigFilePlayerController::VictoryConfigGetTests()
{
	//Basic Syntax
	/*
	bool GetString(
	const TCHAR* Section,
	const TCHAR* Key,
	FString& Value,
	const FString& Filename
	);
	*/

	if (!GConfig) return;
	//~~

	//Retrieve Default Game Type
	FString ValueReceived;
	GConfig->GetString(
		TEXT("/Script/Engine.WorldInfo"),
		TEXT("GlobalDefaultGameType"),
		ValueReceived,
		GGameIni
		);

	ClientMessage("GlobalDefaultGameType");
	ClientMessage(ValueReceived);

	//Retrieve Max Objects not considered by GC
	int32 IntValueReceived = 0;
	GConfig->GetInt(
		TEXT("Core.System"),
		TEXT("MaxObjectsNotConsideredByGC"),
		IntValueReceived,
		GEngineIni
		);

	ClientMessage("MaxObjectsNotConsideredByGC");
	ClientMessage(FString::FromInt(IntValueReceived));

	//Retrieve Near Clip Plane (how close things can get to camera)
	float floatValueReceived = 0;
	GConfig->GetFloat(
		TEXT("/Script/Engine.Engine"),
		TEXT("NearClipPlane"),
		floatValueReceived,
		GEngineIni
		);

	ClientMessage("NearClipPlane");
	ClientMessage(FString::SanitizeFloat(floatValueReceived));
}

//write to existing Game.ini
//the results get stored in YourGameDir\Saved\Config\Windows
void ARWConfigFilePlayerController::VictoryConfigSetTests()
{
	if (!GConfig) return;
	//~~

	//New Section to Add
	FString VictorySection = "Victory.Core";

	//String
	GConfig->SetString(
		*VictorySection,
		TEXT("RootDir"),
		TEXT("E:\UE4\IsAwesome"),
		GGameIni
		);

	//FColor
	GConfig->SetColor(
		*VictorySection,
		TEXT("Red"),
		FColor(255, 0, 0, 255),
		GGameIni
		);

	//FVector
	GConfig->SetVector(
		*VictorySection,
		TEXT("PlayerStartLocation"),
		FVector(0, 0, 512),
		GGameIni
		);

	//FRotator
	GConfig->SetRotator(
		*VictorySection,
		TEXT("SunRotation"),
		FRotator(-90, 0, 0),
		GGameIni
		);

	//ConfigCacheIni.h
	//void Flush( bool Read, const FString& Filename=TEXT("") );
	GConfig->Flush(false, GGameIni);
}

void ARWConfigFilePlayerController::Flush()
{
	GConfig->Flush(false, GGameIni);
}