#pragma once

#include "MyProject.h"
#include "Form.h"

#include "SlateForm.generated.h"

UCLASS(config = Game)
//class USlateForm : public UWindow
class USlateForm : public UForm
{
	// GENERATED_BODY()			// �����Զ�����һ�����캯��
	GENERATED_UCLASS_BODY() // ���Զ�����һ�� USlateForm(const FObjectInitializer& ObjectInitializer) ���캯��

public:
	//USlateForm(const FObjectInitializer& ObjectInitializer);
	USlateForm();
};