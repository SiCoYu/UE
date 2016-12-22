#pragma once

#include "Widgets/SCompoundWidget.h"	// SCompoundWidget

class SSlateWidget : public SCompoundWidget
{
	SSlateWidget();
	SLATE_BEGIN_ARGS(SSlateWidget)
	{}

	SLATE_ATTRIBUTE(FText, MessageText)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};