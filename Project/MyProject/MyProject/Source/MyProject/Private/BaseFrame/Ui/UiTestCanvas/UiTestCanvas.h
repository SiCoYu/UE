#pragma once

#include "MyProject.h"
#include "UMGForm.h"
#include "UITestCanvas.generated.h"

UCLASS(config = Game)
class UUiTestCanvas : public UUMGForm
{
	GENERATED_BODY()

protected:
	TArray<FName> m_namedSlotArr;		// 所有的 NamedSlot 的名字
	UOverlay* m_overlay;				// 一个层
	UNamedSlot* m_namedSlot;				// NamedSlot

protected:
	void loadCanvas();		// 加载有 Canvas 的 UI
	void loadNoCanvas();	// 加载没有 Canvas 的 UI
	void loadCanvasWithNoCanvas();	// 将 NoCanvas 放到 Canvas 上
	void loadNamedSlot();	// 加载有 Named Slot 控件的 UI
	void loadOverlay();		// 加载 Overlay 

	void unloadCanvas();	// 卸载

	void testMove(UWidget* ptr);
	void testHide(UWidget* ptr);

public:
	UUiTestCanvas(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

	virtual void onReady();
};