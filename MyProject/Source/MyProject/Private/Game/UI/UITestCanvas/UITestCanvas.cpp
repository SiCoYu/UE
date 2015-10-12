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
	//loadCanvas();
	//loadNoCanvas();
	//loadNamedSlot();
	loadOverlay();
	m_umgWidget->AddToViewport();
	//EngineApi::addEventHandle((UButton*)m_umgWidget->GetWidgetFromName("Button_32"), (UObject*)this, "OnConfirmGeneric");
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
}

void UUITestCanvas::loadNoCanvas()
{
	loadUWidget(TEXT("/Game/UMG/UITestCanvas_NoCanvas.UITestCanvas_NoCanvas_C"));
}

void UUITestCanvas::loadCanvasWithNoCanvas()
{
	
}

void UUITestCanvas::loadNamedSlot()
{
	loadUWidget(TEXT("/Game/UMG/UITestNamedSlot.UITestNamedSlot_C"));

	// 目前已经有点 NamedSlot 是 "NamedSlot_28"
	m_umgWidget->GetSlotNames(m_namedSlotArr);
}

void UUITestCanvas::loadOverlay()
{
	loadUWidget(TEXT("/Game/UMG/UITestOveray.UITestOveray_C"));
	m_overlay = (UOverlay*)(m_umgWidget->GetWidgetFromName("Overlay_17"));
}