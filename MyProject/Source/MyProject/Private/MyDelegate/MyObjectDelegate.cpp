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