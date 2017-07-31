//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/Platform.h"
#include "HideOSMouseCursor.generated.h"

/**
* @brief https://wiki.unrealengine.com/How_to_Hide_OS_Mouse_Cursor_Anytime,_Anywhere
*/

UCLASS()
class UHideOSMouseCursor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Show/Hide OS Mouse Cursor
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	static FORCEINLINE void SetOSCursorVisible(bool MakeVisible)
	{
		FSlateApplication::Get().GetPlatformApplication()->Cursor->Show(MakeVisible);
	}
};