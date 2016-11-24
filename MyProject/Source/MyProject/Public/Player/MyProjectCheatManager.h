#pragma once

#include "MyProjectCheatManager.generated.h"

// E:/Self/Self/unreal/UE-GIT/UE/MyProject/Source/MyProject/Public/Player/MyProjectCheatManager.h(7): error : Parent class declared within 'PlayerController'.  Cannot override within class with 'MyProjectCheatManager' since it isn't a child
//UCLASS(Within=UMyProjectCheatManager)
UCLASS(Within = MyProjectPlayerController)
class UMyProjectCheatManager : public UCheatManager
{
	GENERATED_UCLASS_BODY()
};
