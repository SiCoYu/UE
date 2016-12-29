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