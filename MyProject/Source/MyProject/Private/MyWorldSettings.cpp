#include "MyProject.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyWorldSettings.h"

AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ÿһ���ؿ�������ײ����
	PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
}