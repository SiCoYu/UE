#pragma once

#include "MyProject.h"
#include "CustomComponents.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Actor_Custom_Components,_Edit_Variables_Per_Instance_In_Level_Editor
 */

//Choosing a class group and making it BlueprintSpawnableComponent
UCLASS(ClassGroup = JoyMech, meta = (BlueprintSpawnableComponent))
class UCustomComponents : public UActorComponent
{
	GENERATED_BODY()
public:
	UCustomComponents(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="JoyNav")
	//FString CustomNavGroup;

	/** Density Core Value, the smaller the more dense, density = 360/JoyNavDensity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoyNav")
	float JoyNavDensity;

	/** Draw Units! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoyNav")
	bool DoDrawUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoyNav")
	bool DoDrawJoyNavDisplayInfo;

	/** Each radius gets its own layers of units! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoyNav")
	TArray<int32> RadiusLevels;

	/** Trim out units that are closer than Radius * TrimPercent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JoyNav")
	float TrimPercent;

	//.. etc
};