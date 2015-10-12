#pragma once

#include "MyProject.h"
#include "FormBase.h"
#include "UMGForm.generated.h"

class UUserWidget;

UCLASS(abstract, config = Game)
class UUMGForm : public UFormBase
{
	GENERATED_BODY()

protected:
	UUserWidget* m_umgWidget;
	//TSharedPtr<SWidget> m_outUserSlateWidget;
	//TSharedRef<SWidget> m_rootWidget;

protected:
	void loadUWidget(const TCHAR* name);
};