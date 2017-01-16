#include "MyProject.h"
#include "MyTPWorldSettings.h"
#include "MyTPPhysicsCollisionHandler.h"
#include "MyTPGameMode.h"

AMyTPWorldSettings::AMyTPWorldSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// ÿһ���ؿ�������ײ����
	this->PhysicsCollisionHandlerClass = UMyTPPhysicsCollisionHandler::StaticClass();
	this->DefaultGameMode = AMyTPGameMode::StaticClass();	// ���û�����ã��������������õ�
}