#include "MyProject.h"
#include "UIPack.h"
#include "Common.h"

UUIPack::UUIPack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	m_umgWidget->AddToViewport();
	EngineApi::addEventHandle((UButton*)m_umgWidget->GetWidgetFromName("Button_16"), (UObject*)this, "OnConfirmGeneric");

	//TSharedPtr<SWidget> m_outUserSlateWidget;
	//TSharedRef<SWidget> m_rootWidget = m_umgWidget->MakeViewportWidget(m_outUserSlateWidget);
	//GEngine->GameViewport->AddViewportWidgetContent(m_rootWidget);

	//UButton* ccc = (UButton*)m_umgWidget->GetWidgetFromName("Button_14");
	//TScriptDelegate<FWeakObjectPtr> ddd;
	//ddd.BindUFunction((UObject *)this, "OnConfirmGeneric");
	//ccc->OnClicked.Add(ddd);
}

void UUIPack::OnConfirmGeneric()
{

}