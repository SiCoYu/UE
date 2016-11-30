#pragma once

#include "GameFramework/Actor.h"
#include "CustomComponents.h"
#include "CustomComponentsActor.generated.h"

/**
* @brief https://wiki.unrealengine.com/Actor_Custom_Components,_Edit_Variables_Per_Instance_In_Level_Editor
*/

UCLASS(config = Game)
class ACustomComponentsActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ACustomComponentsActor(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(VisibleAnywhere, Category = JoySMAHighest, meta = (ExposeFunctionCategories = "JoyNav", AllowPrivateAccess = "true"))
	UCustomComponents* JoyNavComp;
};