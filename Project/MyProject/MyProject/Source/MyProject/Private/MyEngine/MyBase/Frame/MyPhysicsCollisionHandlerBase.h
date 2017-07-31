#pragma once

#include "PhysicsEngine/PhysicsCollisionHandler.h"	// UPhysicsCollisionHandler
#include "MyPhysicsCollisionHandlerBase.generated.h"

/**
 * @brief
 ����������
 DefaultEngine.ini
 [/Script/EngineSettings.GameMapsSettings]
 PhysicsCollisionHandlerClassName=/Script/MyProject.MyTPPhysicsCollisionHandler
 */

UCLASS()
class UMyPhysicsCollisionHandlerBase : public UPhysicsCollisionHandler
{
	GENERATED_UCLASS_BODY()
};