#pragma once

#include "UMGForm.h"
#include "AuxButton.h"
#include "MySharedPointer.h"
#include "TypeDef.h"

#include "UIFunctionBar.generated.h"

using namespace MyNS;

namespace MyNS
{
	class IDispatchObject;
}

using namespace MyNS;

UCLASS(config = Game)
class UUiFunctionBar : public UUMGForm
{
	GENERATED_BODY()

protected:
	MySharedPtr<AuxButton> mTestButton;
	AuxButton* mTestComBtn;
	AuxButton* mTestLoadTextureBtn;
	AuxButton* mTestLoadMaterialBtn;
	AuxButton* mTestChangeMaterialBtn;

public:
	UUiFunctionBar(const FObjectInitializer& ObjectInitializer);

public:
	virtual void onInit() override;
	virtual void onReady() override;
	virtual void onExit() override;

public:
	// UFunction* UObject::FindFunction( FName InName ) const
	// �󶨵� UMG �еĺ�����һ��Ҫ��ӵ�������У���Ϊ��Ҫ�� FindFunction �ӿ�ȥ�������ȥ��������ӿڣ��������ӣ��Ͳ��ܲ��ҵ�
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestButtonTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestComBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestLoadTextureBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestLoadMaterialBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onTestChangeMaterialBtnTouch();
	UFUNCTION(BlueprintCallable, Category = "MyButton")
	void onLevelLoaded();

public:
	void onLevelLoadedDispatch(uint eventId, IDispatchObject* dispObj);
};