#pragma once

#include "MyProject.h"
#include "Form.h"

#include "SlateForm.generated.h"

UCLASS(config = Game)
//class USlateForm : public UWindow
class USlateForm : public UForm
{
	// GENERATED_BODY()			// 不会自动生成一个构造函数
	GENERATED_UCLASS_BODY() // 会自动定义一个 USlateForm(const FObjectInitializer& ObjectInitializer) 构造函数

public:
	//USlateForm(const FObjectInitializer& ObjectInitializer);
	USlateForm();
};