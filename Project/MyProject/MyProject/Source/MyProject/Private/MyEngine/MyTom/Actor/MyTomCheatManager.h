#pragma once

#include "MyCheatManagerBase.h"
#include "MyTomCheatManager.generated.h"

// E:/Self/Self/unreal/UE-GIT/UE/MyProject/Source/MyProject/Public/Player/MyCheatManager.h(7): error : Parent class declared within 'PlayerController'.  Cannot override within class with 'MyCheatManager' since it isn't a child
//UCLASS(Within=UMyCheatManager)
UCLASS(Within = MyFlyPlayerController)
class UMyTomCheatManager : public UMyCheatManagerBase
{
	GENERATED_UCLASS_BODY()
};