#include "MyProject.h"
#include "UMGForm.h"
#include "MyCtx.h"

void UMGForm::loadUWidget(const TCHAR* name)
{
	UClass* widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, name);
	if (widgetClass != NULL)
	{
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, GEngine->GameViewport->GetWorld()->GetGameInstance()));
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, MyCtx::getSingletonPtr()->getGameInstance()));
		m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, MyCtx::getSingletonPtr()->getEngineApi()->getGameInstance()));
	}
}