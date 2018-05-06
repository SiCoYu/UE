#pragma once

#include "Widgets/SCompoundWidget.h"	// SCompoundWidget

/**
 * @URL https://wiki.unrealengine.com/Slate,_How_to_Make_Fancy_Custom_SButtons
 */

class SUiCustomButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUiCustomButton)
	{}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	//Buttons
	TSharedPtr<SButton> RefreshButton;
	TSharedPtr<STextBlock> RefreshButtonText;
	TSharedPtr<SButton> ClearTileButton;

public:
	void SetCursor();
	void SetToolTip();

public:
	// Engine\Source\Programs\CrashReporter\CrashReportClient\Private\SCrashReportClient.cpp
	FReply RefreshButtonPressed();
	FReply ClearButtonPressed();
};