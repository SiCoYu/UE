#pragma once

#include "UObject/Object.h"	// UObject
#include "Delegates/DelegateCombinations.h"		// DECLARE_DELEGATE_ThreeParams
#include "Engine/World.h"		// InitializationValues
#include "Delegates/IDelegateInstance.h"	// FDelegateHandle
#include "MyObjectDelegate.generated.h"

// 定义一个 Delegate 类型
DECLARE_DELEGATE_ThreeParams(UMyObjectCommonDelegate, int, int, bool);

/**
 * @brief Delegate
 */

UCLASS(config = Game)
class UMyObjectDelegate : public UObject
{
	GENERATED_UCLASS_BODY()

	using InitializationValues = UWorld::InitializationValues;

public:
	UMyObjectCommonDelegate MyObjectCommonDelegate;

public:
	void handle(int aaa, int bbb, bool ccc);

protected:
	// Engine\Source\Runtime\Engine\Private\PhysicsEngine2D\Box2DIntegration.h
	FWorldDelegates::FWorldInitializationEvent::FDelegate OnWorldCreatedDelegate;
	FWorldDelegates::FWorldInitializationEvent::FDelegate OnWorldDestroyedDelegate;

	FDelegateHandle OnWorldCreatedDelegateHandle;
	FDelegateHandle OnWorldDestroyedDelegateHandle;

	void addWorldHandle();
	void removeWorldHandle();
	void OnPreWorldInitialization(UWorld* world, const InitializationValues IVS = InitializationValues());
	void OnPostWorldInitialization(UWorld* world, const InitializationValues IVS = InitializationValues());
};