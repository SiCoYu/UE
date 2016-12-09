#pragma once

/**
 * @brief https://wiki.unrealengine.com/Static_Function_Libraries,_Your_Own_Version_of_UE4_C%2B%2B,_No_Engine_Compile_Times
 */

USTRUCT()
struct FQuadVRect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVRect Rects[4];

	//base constructor
	FQuadVRect()
	{
	}
};