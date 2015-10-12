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
	loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	m_umgWidget->AddToViewport();
	EngineApi::addEventHandle((UButton*)m_umgWidget->GetWidgetFromName("Button_16"), (UObject*)this, "OnConfirmGeneric");
}

void UUITestCanvas::OnConfirmGeneric()
{
	g_pTableSys->getItem(TableID::TABLE_OBJECT, 100);

	UPackage* tblPkg = CreatePackage(NULL, TEXT("/Game/Table/ObjectBase_client"));
	UDataAssetLoadItem* ObjectPtr = LoadObject<UDataAssetLoadItem>(tblPkg, TEXT("/Game/Table/ObjectBase_client"));
}