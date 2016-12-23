#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "UMG.h"
#include "SlateForm.h"

class SSlateLog : public SSlateWidget
{
public:
	SSlateLog();
	SLATE_BEGIN_ARGS(SSlateLog)
	{}

	//SLATE_TEXT_ARGUMENT(MessageText)
	SLATE_ATTRIBUTE(FText, MessageText)

	SLATE_END_ARGS()	

	void Construct(const FArguments& InArgs);

	//TSubclassOf<class UUserWidget>  WidgetClass;
};
