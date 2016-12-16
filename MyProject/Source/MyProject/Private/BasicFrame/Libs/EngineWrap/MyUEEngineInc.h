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

#endif