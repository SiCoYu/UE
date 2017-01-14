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
	// 绑定到 UMG 中的函数，一定要添加到虚拟机中，因为需要从 FindFunction 接口去虚拟机中去查找这个接口，如果不添加，就不能查找到
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestButtonTouch();
};