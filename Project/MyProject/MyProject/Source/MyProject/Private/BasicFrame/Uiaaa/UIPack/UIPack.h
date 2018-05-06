#pragma once

#include "UMGForm.h"
#include "UIPack.generated.h"

/**
 *@brief ���ʹ�� UMG ������ʹ�� UCLASS ����ϵͳ�󶨣�Ȼ�����ǾͿ��԰��Լ����¼���
 */
UCLASS(config = Game)
class UUIPack : public UUMGForm
{
	GENERATED_BODY()

public:
	UUIPack(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

	virtual void onReady();
};