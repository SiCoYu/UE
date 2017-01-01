#include "MyProject.h"
#include "MyObjectDelegate.h"

UMyObjectDelegate::UMyObjectDelegate(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// ����һ: ����¼�
	//MyObjectCommonDelegate = UMyObjectCommonDelegate::CreateUObject(this, &UMyObjectDelegate::handle);
	// ������: ����¼�
	MyObjectCommonDelegate.BindUObject(this, &UMyObjectDelegate::handle);
	MyObjectCommonDelegate.Execute(10, 10, true);
}

void UMyObjectDelegate::handle(int aaa, int bbb, bool ccc)
{
	
}

void UMyObjectDelegate::bindWorldHandle()
{
	FWorldDelegates::OnPreWorldInitialization.BindUObject(this, &UMyObjectDelegate::OnPreWorldInitialization);
	FWorldDelegates::OnPostWorldInitialization.BindUObject(this, &UMyObjectDelegate::OnPostWorldInitialization);
}

void UMyObjectDelegate::OnPreWorldInitialization(UWorld* world, const InitializationValues IVS)
{

}

void UMyObjectDelegate::OnPostWorldInitialization(UWorld* world, const InitializationValues IVS)
{

}