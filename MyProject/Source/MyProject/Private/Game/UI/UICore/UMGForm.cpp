#include "MyProject.h"
#include "UMGForm.h"

void UMGForm::loadUWidget(const TCHAR* name)
{
	UClass* widgetClass = StaticLoadClass(UUserWidget::StaticClass(), NULL, name);
	if (widgetClass != NULL)
	{
		m_umgWidget = Cast<UUserWidget>(StaticConstructObject(widgetClass));
	}
}