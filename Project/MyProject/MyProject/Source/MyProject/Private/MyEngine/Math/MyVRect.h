#pragma once

#include "Math/Vector2D.h"
#include "MyVRect.generated.h"

/**
* @brief https://wiki.unrealengine.com/Static_Function_Libraries,_Your_Own_Version_of_UE4_C%2B%2B,_No_Engine_Compile_Times
*/

USTRUCT()
struct FMyVRect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector2D Min;

	UPROPERTY()
	FVector2D Max;

	//overloaded constructor
	FMyVRect(const FVector2D& VPoint1, const FVector2D& VPoint2)
	{
		//drag topleft to bottom right
		if (VPoint1.X < VPoint2.X &&
			VPoint1.Y < VPoint2.Y
			) {
			Min = VPoint1;
			Max = VPoint2;
		}

		//drag from bottom right to top left
		else if (VPoint1.X > VPoint2.X &&
			VPoint1.Y > VPoint2.Y
			) {
			Min = VPoint2;
			Max = VPoint1;
		}

		//drag from bottom left to top right
		else if (VPoint1.X < VPoint2.X &&
			VPoint1.Y > VPoint2.Y
			) {
			Min = FVector2D(VPoint1.X, VPoint2.Y);
			Max = FVector2D(VPoint2.X, VPoint1.Y);
		}
	}

	//base constructor
	FMyVRect()
	{
		Min = FVector2D(0, 0);
		Max = FVector2D(500, 500);
	}
};