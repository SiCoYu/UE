#pragma once

#include "MyProject.h"
#include "UMGForm.h"
#include "UITestCanvas.generated.h"

UCLASS(config = Game)
class UUITestCanvas : public UUMGForm
{
	GENERATED_BODY()

protected:
	TArray<FName> m_namedSlotArr;		// ���е� NamedSlot ������
	UOverlay* m_overlay;				// һ����
	UNamedSlot* m_namedSlot;				// NamedSlot

protected:
	void loadCanvas();		// ������ Canvas �� UI
	void loadNoCanvas();	// ����û�� Canvas �� UI
	void loadCanvasWithNoCanvas();	// �� NoCanvas �ŵ� Canvas ��
	void loadNamedSlot();	// ������ Named Slot �ؼ��� UI
	void loadOverlay();		// ���� Overlay 

public:
	UUITestCanvas(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

	virtual void onReady();
};