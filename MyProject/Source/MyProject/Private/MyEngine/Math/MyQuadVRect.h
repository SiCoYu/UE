#pragma once

#include "MyVRect.h"
#include "MyQuadVRect.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Static_Function_Libraries,_Your_Own_Version_of_UE4_C%2B%2B,_No_Engine_Compile_Times
 */

USTRUCT()
struct FMyQuadVRect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FMyVRect Rects[4];

	//base constructor
	FMyQuadVRect()
	{
	}
};