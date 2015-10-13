#include "MyProject.h"
#include "UITestCanvas.h"
#include "Common.h"
#include "BinaryLoadItem.h"
#include "Ctx.h"
#include "TableSys.h"
#include "DataAssetLoadItem.h"

UUITestCanvas::UUITestCanvas(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UUITestCanvas::onReady()
{
	loadCanvas();
	//loadNoCanvas();
	//loadNamedSlot();
	//loadOverlay();
	//loadCanvasWithNoCanvas();
	//EngineApi::addEventHandle((UButton*)m_umgWidget->GetWidgetFromName("Button_32"), (UObject*)this, "OnConfirmGeneric");
	//unloadCanvas();
}

void UUITestCanvas::OnConfirmGeneric()
{
	//g_pTableSys->getItem(TableID::TABLE_OBJECT, 100);

	//UPackage* tblPkg = CreatePackage(NULL, TEXT("/Game/Table/ObjectBase_client"));
	//UDataAssetLoadItem* ObjectPtr = LoadObject<UDataAssetLoadItem>(tblPkg, TEXT("/Game/Table/ObjectBase_client"));
}

void UUITestCanvas::loadCanvas()
{
	loadUWidget(TEXT("/Game/UMG/UITestCanvas_Canvas.UITestCanvas_Canvas_C"));
	//loadUWidget(TEXT("/CacheData/UMG/UITestCanvas_Canvas.UITestCanvas_Canvas_C"));
	m_umgWidget->AddToViewport();
	UButton* pButton = (UButton*)(m_umgWidget->GetWidgetFromName("Button_32"));
	UButtonSlot* pBtnSlot = Cast<UButtonSlot>(pButton->GetContentSlot());

	// 测试移动位置
	//testMove(pButton);

	// 测试隐藏控件
	//testHide(pButton);
}

void UUITestCanvas::loadNoCanvas()
{
	loadUWidget(TEXT("/Game/UMG/UITestCanvas_NoCanvas.UITestCanvas_NoCanvas_C"));
	m_umgWidget->AddToViewport();
}

void UUITestCanvas::loadCanvasWithNoCanvas()
{
	UClass* widgetClass = nullptr;
	widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, TEXT("/Game/UMG/UITestCanvas_Canvas.UITestCanvas_Canvas_C"));
	UUserWidget* parentWidget = nullptr;
	if (nullptr != widgetClass)
	{
		parentWidget = NewObject<UUserWidget>(g_pEngineApi->getGameInstance(), widgetClass);
		parentWidget->AddToViewport();
	}

	UUserWidget* childWidget = nullptr;

	widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, TEXT("/Game/UMG/UITestCanvas_NoCanvas.UITestCanvas_NoCanvas_C"));
	if (nullptr != widgetClass)
	{
		childWidget = NewObject<UUserWidget>(g_pEngineApi->getGameInstance(), widgetClass);
	}

	if (nullptr != parentWidget && nullptr != childWidget)
	{
		parentWidget->SetContentForSlot("NamedSlot_24", childWidget);
	}
}

void UUITestCanvas::loadNamedSlot()
{
	loadUWidget(TEXT("/Game/UMG/UITestNamedSlot.UITestNamedSlot_C"));
	//loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	m_umgWidget->AddToViewport();	// 一定要先 AddToViewport ，然后再获取控件，否则 GetWidgetFromName 的时候会报错
	// 目前已经有点 NamedSlot 是 "NamedSlot_28"
	m_umgWidget->GetSlotNames(m_namedSlotArr);
	m_namedSlot = (UNamedSlot*)(m_umgWidget->GetWidgetFromName("NamedSlot_28"));
	//UWidget* widget = m_umgWidget->GetWidgetFromName("Button_16");
}

void UUITestCanvas::loadOverlay()
{
	loadUWidget(TEXT("/Game/UMG/UITestOveray.UITestOveray_C"));
	m_umgWidget->AddToViewport();
	// Overlay_17 已经有的 Overlay 
	m_overlay = (UOverlay*)(m_umgWidget->GetWidgetFromName("Overlay_17"));
	UWidget* widget = m_umgWidget->GetWidgetFromName("Button_32");
}

void UUITestCanvas::unloadCanvas()
{
	m_umgWidget->RemoveFromViewport();
	m_umgWidget = nullptr;
}

void UUITestCanvas::testMove(UWidget* ptr)
{
	UCanvasPanelSlot* pPanelSlot = Cast<UCanvasPanelSlot>(ptr->Slot);	// 终于找到 UButton 的 UCanvasPanelSlot 元素了
	//UCanvasPanelSlot* pPanelSlot = Cast<UCanvasPanelSlot>(pButton->GetContentSlot());
	pPanelSlot->SetPosition(FVector2D(700, 600));

	// 获取 CanvasPanel 
	//UCanvasPanel* pCanvasPanel = (UCanvasPanel*)(m_umgWidget->GetWidgetFromName("UCanvasPanel"));
	// UCanvasPanel 是没有 UPanelSlot 的，因为 UCanvasPanel 继承 UPanelWidget，而 UButton 继承 UContentWidget ，而 GetContentSlot 是在 UContentWidget 中的
	//UCanvasPanelSlot* pPanelSlot = Cast<UCanvasPanelSlot>(pCanvasPanel->GetContentSlot());
}

void UUITestCanvas::testHide(UWidget* ptr)
{
	//ptr->Visibility = ESlateVisibility::Hidden;
	ptr->SetVisibility(ESlateVisibility::Hidden);
}