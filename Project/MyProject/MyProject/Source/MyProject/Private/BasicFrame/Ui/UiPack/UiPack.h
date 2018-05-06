#pragma once

#include "UMGForm.h"
#include "UIPack.generated.h"

/**
 *@brief ���ʹ�� UMG ������ʹ�� UCLASS ����ϵͳ�󶨣�Ȼ�����ǾͿ��԰��Լ����¼���
 */
UCLASS(config = Game)
class UUiPack : public UUMGForm
{
	GENERATED_BODY()

public:
	UUiPack(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

	virtual void onReady();
};