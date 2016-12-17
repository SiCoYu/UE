#pragma once

#include "Widgets/SCompoundWidget.h"	// SCompoundWidget

/**
 * @URL https://wiki.unrealengine.com/Slate,_How_to_Make_Fancy_Custom_SButtons
 */

class SUICustomButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUICustomButton)
	{}

	SLATE_END_ARGS()

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
};