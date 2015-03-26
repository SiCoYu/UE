#include "MyProject.h"
#include "UIPack.h"

UIPack::UIPack()
{
	loadUWidget(TEXT("/Game/Blueprints/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	m_umgWidget->AddToViewport();

	//TSharedPtr<SWidget> m_outUserSlateWidget;
	//TSharedRef<SWidget> m_rootWidget = m_umgWidget->MakeViewportWidget(m_outUserSlateWidget);
	//GEngine->GameViewport->AddViewportWidgetContent(m_rootWidget);

	//UButton* ccc = (UButton*)m_umgWidget->GetWidgetFromName("Button_14");
	//TScriptDelegate<FWeakObjectPtr> ddd;
	//ddd.BindUFunction((UObject *)this, "OnConfirmGeneric");
	//ccc->OnClicked.Add(ddd);
}