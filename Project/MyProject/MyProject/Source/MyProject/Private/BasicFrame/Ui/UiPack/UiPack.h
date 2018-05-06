#pragma once

#include "UMGForm.h"
#include "UIPack.generated.h"

/**
 *@brief 如果使用 UMG ，尽量使用 UCLASS 生成系统绑定，然后我们就可以绑定自己的事件了
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