#pragma once

#include "UMGForm.h"
#include "UIFunctionBar.generated.h"

UCLASS(config = Game)
class UUIFunctionBar : public UUMGForm
{
	GENERATED_BODY()

public:
	UUIFunctionBar(const FObjectInitializer& ObjectInitializer);

public:
	virtual void onReady() override;

public:
	// UFunction* UObject::FindFunction( FName InName ) const
	// �󶨵� UMG �еĺ�����һ��Ҫ��ӵ�������У���Ϊ��Ҫ�� FindFunction �ӿ�ȥ�������ȥ��������ӿڣ��������ӣ��Ͳ��ܲ��ҵ�
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestButtonTouch();
};