#include "MyProject.h"
#include "UMGForm.h"
#include "Ctx.h"
#include "EngineApi.h"

void UMGForm::loadUWidget(const TCHAR* name)
{
	UClass* widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, name);
	if (widgetClass != NULL)
	{
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, GEngine->GameViewport->GetWorld()->GetGameInstance()));
		//m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, MyCtx::getSingletonPtr()->getGameInstance()));
		m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass, Ctx::getSingletonPtr()->getEngineApi()->getGameInstance()));
	}
}