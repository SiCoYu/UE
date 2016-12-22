#ifndef __MyUEEngineInc_H
#define __MyUEEngineInc_H

/**
 * @brief 最小 UE 包含头文件
 */
 // #include "Platform.h"
#include "Core.h"		// "Platform.h" 已经包含在 "Core.h" 中了
 //#include "ICUUtilities.h"

#include "UObject/Object.h" // UObject : public UObjectBaseUtility
#include "Math/Vector.h"	// FVector
#include "GameFramework/Actor.h"	// AActor
#include "Components/StaticMeshComponent.h"		// UStaticMeshComponent
#include "GenericPlatform/GenericPlatformMath.h"	// Max

#include "Containers/UnrealString.h"	// FString
#include "Engine/EngineTypes.h"	// FTimerHandle
#include "UObject/Object.h"	// UObject

#include "Templates/SharedPointer.h"
#include "SocketSubsystem.h"
#include "Internationalization/Text.h"	// FText
#include "Widgets/SCompoundWidget.h"	// SCompoundWidget

#include "HAL/Platform.h"	// int32
#include "GenericPlatform/GenericPlatform.h"	// int32
#include "Templates/Casts.h"	// Cast
#include "Input/Events.h"	// FKeyEvent

#include "UObject/ObjectMacros.h"	// GENERATED_USTRUCT_BODY
#include "Widgets/Views/STableRow.h"	// ITableRow
#include "Containers/Array.h"	// TArray
#include "Widgets/SWindow.h"	// SWindow

#include "Framework/Application/SlateApplication.h"		// FSlateApplication
#include "Application/SlateWindowHelper.h"	// FSlateWindowHelper
#include "IDesktopPlatform.h"	// FOpenLauncherOptions
#include "UObject/WeakObjectPtrTemplates.h"	// TWeakObjectPtr

#include "Input/Reply.h"		// FReply
#include "Widgets/SUserWidget.h"	// SUserWidget\FArguments
#include "GameFramework/WorldSettings.h"	// UWorldSettings
#include "Engine/Console.h"		// UConsole

#include "PhysicsEngine/PhysicsCollisionHandler.h"	// UPhysicsCollisionHandler
#include "GameFramework/SaveGame.h"		// USaveGame
#include "GameFramework/PlayerStart.h"		// APlayerStart
#include "GameMapsSettings.h"	// UGameMapsSettings

#include "Templates/SubclassOf.h"		// TSubclassOf

#endif