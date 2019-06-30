#include "MyProject.h"
#include "CanvasItem.h"
#include "MyDialog.h"
//#include "EngineGlobals.h"		// GEngine
#include "Engine.h"
#include "MyEditText.h"
#include "MyChatWidget.h"
#include "SChatMsg.h"
#include "MyPlayerState.h"
#include "MySlateTabWidget.h"
#include "MyHudBase.h"

// https://wiki.unrealengine.com/Slate,_Edit_Text_Widget,_Custom_Rendering_%26_Any_TrueTypeFont
#define VICTORY_ALLOW_TICK if(!GEngine) return; if(!GEngine->GameViewport) return;

#define LOCTEXT_NAMESPACE "MyProject.HUD"

AMyHudBase::AMyHudBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void AMyHudBase::DrawHUD()
{
	Super::DrawHUD();

	if (Canvas == nullptr)
	{
		return;
	}

	//this->DrawText();
	//this->AddDialog();
	//this->DrawHUD_ChatSystem();
	//this->DrawHUD_EditText();
}

void AMyHudBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 暂时屏蔽显示界面
	//if (GEngine && GEngine->GameViewport) // make sure our screen is ready for the widget
	//{
	//	SAssignNew(MyUIWidget, SMyChatWidget).OwnerHUD(this); // add the widget and assign it to the var
	//	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));
	//}
}

void AMyHudBase::BeginPlay()
{
	// 暂时屏蔽
	// this->BeginPlay_LoadStyleWidget();
	// 暂时屏蔽
	//this->BeginPlay_SlateTab();
}