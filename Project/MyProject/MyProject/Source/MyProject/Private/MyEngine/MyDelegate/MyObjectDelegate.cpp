#include "MyProject.h"
#include "MyObjectDelegate.h"

UMyObjectDelegate::UMyObjectDelegate(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// 方法一: 添加事件
	//MyObjectCommonDelegate = UMyObjectCommonDelegate::CreateUObject(this, &UMyObjectDelegate::handle);
	// 方法二: 添加事件
	MyObjectCommonDelegate.BindUObject(this, &UMyObjectDelegate::handle);
	MyObjectCommonDelegate.Execute(10, 10, true);
}

void UMyObjectDelegate::handle(int aaa, int bbb, bool ccc)
{
	
}

void UMyObjectDelegate::addWorldHandle()
{
	// 方法一
	// Engine\Source\Runtime\GameplayAbilities\Private\GameplayCueManager.cpp
	FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UMyObjectDelegate::OnPreWorldInitialization);
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UMyObjectDelegate::OnPostWorldInitialization);

	// 方法二
	// Engine\Source\Runtime\Engine\Private\PhysicsEngine2D\Box2DIntegration.cpp
	OnWorldCreatedDelegate = FWorldDelegates::FWorldInitializationEvent::FDelegate::CreateUObject(this, &UMyObjectDelegate::OnPreWorldInitialization);
	OnWorldDestroyedDelegate = FWorldDelegates::FWorldInitializationEvent::FDelegate::CreateUObject(this, &UMyObjectDelegate::OnPostWorldInitialization);

	OnWorldCreatedDelegateHandle = FWorldDelegates::OnPreWorldInitialization.Add(OnWorldCreatedDelegate);
	OnWorldDestroyedDelegateHandle = FWorldDelegates::OnPostWorldInitialization.Add(OnWorldDestroyedDelegate);
}

void UMyObjectDelegate::removeWorldHandle()
{
	// 方法一，这种注册的事件不能移除
	//FWorldDelegates::OnPreWorldInitialization.RemoveUObject(this, &UMyObjectDelegate::OnPreWorldInitialization);
	//FWorldDelegates::OnPostWorldInitialization.RemoveUObject(this, &UMyObjectDelegate::OnPostWorldInitialization);

	// 方法二
	FWorldDelegates::OnPreWorldInitialization.Remove(OnWorldCreatedDelegateHandle);
	FWorldDelegates::OnPreWorldFinishDestroy.Remove(OnWorldDestroyedDelegateHandle);
}

void UMyObjectDelegate::OnPreWorldInitialization(UWorld* world, const InitializationValues IVS)
{

}

void UMyObjectDelegate::OnPostWorldInitialization(UWorld* world, const InitializationValues IVS)
{

}