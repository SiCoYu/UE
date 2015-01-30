// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "UMG.h"
#include "SlateForm.h"

class UILog : public SCompoundWidget, SlateForm
{
public:
	UILog();
	SLATE_BEGIN_ARGS(UILog)
	{}

	SLATE_TEXT_ARGUMENT(MessageText)

	SLATE_END_ARGS()	

	void Construct(const FArguments& InArgs);

	//TSubclassOf<class UUserWidget>  WidgetClass;
};
