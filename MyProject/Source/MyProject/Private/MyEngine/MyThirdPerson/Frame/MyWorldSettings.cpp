#include "MyProject.h"
#include "MyWorldSettings.h"
#include "MyPhysicsCollisionHandler.h"
#include "MyGameMode.h"

AMyWorldSettings::AMyWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ÿһ���ؿ�������ײ����
	this->PhysicsCollisionHandlerClass = UMyPhysicsCollisionHandler::StaticClass();
	this->DefaultGameMode = AMyGameMode::StaticClass();	// ���û�����ã��������������õ�
}