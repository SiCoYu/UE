#include "MyProject.h"
#include "MyHUD.h"
#include "SWidgetSwitcher.h"
#include "MyStyle.h"
#include "MySlateTabWidget.h"

int FirstTabActive = 1;
int SecondTabActive = 0;

int ftClick = 1;
int stClick = 0;

void SMySlateTabWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;

	TabIndex = 0;

	ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.FillHeight(0.1)

		+ SVerticalBox::Slot()
		.FillHeight(0.8)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
		.FillWidth(0.3)

		+ SHorizontalBox::Slot()
		.FillWidth(0.4)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.FillHeight(0.2)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		[
			SNew(SButton)
			.ContentPadding(-3)
		.OnClicked(this, &SMySlateTabWidget::FirstTabClicked)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.BorderImage(this, &SMySlateTabWidget::GetFirstImageBrush)
		[
			SNew(STextBlock)
			.Font(FSlateFontInfo("Veranda", 54))
		.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Text(FText::FromString("Page One"))
		]
		]
		]
		]

	+ SHorizontalBox::Slot()
		.FillWidth(0.1)

		+ SHorizontalBox::Slot()
		[
			SNew(SButton)
			.ContentPadding(-3)
		.OnClicked(this, &SMySlateTabWidget::SecondTabClicked)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.BorderImage(this, &SMySlateTabWidget::GetSecondImageBrush)
		[
			SNew(STextBlock)
			.Font(FSlateFontInfo("Veranda", 54))
		.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Text(FText::FromString("Page Two"))
		]
		]
		]
		]
		]

	+ SVerticalBox::Slot()
		.FillHeight(0.8)
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(this, &SMySlateTabWidget::GetCurrentTabIndex)
		+ SWidgetSwitcher::Slot()
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Font(FSlateFontInfo("Veranda", 72))
		.Text(FText::FromString("Page One"))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Font(FSlateFontInfo("Veranda", 52))
		.Text(FText::FromString("Page One"))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Font(FSlateFontInfo("Veranda", 32))
		.Text(FText::FromString("Page One"))
		]
		]
		]
	+ SWidgetSwitcher::Slot() // Weapons
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Font(FSlateFontInfo("Veranda", 72))
		.Text(FText::FromString("Page Two"))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Font(FSlateFontInfo("Veranda", 52))
		.Text(FText::FromString("Page Two"))
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor(1, 1, 1, 1))
		.Font(FSlateFontInfo("Veranda", 32))
		.Text(FText::FromString("Page Two"))
		]
		]
		]
		]
		]

	+ SHorizontalBox::Slot()
		.FillWidth(0.3)
		]

	+ SVerticalBox::Slot()
		.FillHeight(0.1)
		];
}

const FSlateBrush* SMySlateTabWidget::GetFirstImageBrush() const
{
	FName BrushName;
	(FirstTabActive == 0) ? BrushName = TEXT("tab_normal") : BrushName = TEXT("tab_active");

	return FMyStyle::Get().GetBrush(BrushName);
}

const FSlateBrush* SMySlateTabWidget::GetSecondImageBrush() const
{
	FName BrushName;
	(SecondTabActive == 0) ? BrushName = TEXT("tab_normal") : BrushName = TEXT("tab_active");

	return FMyStyle::Get().GetBrush(BrushName);
}

FReply SMySlateTabWidget::FirstTabClicked()
{
	TabIndex = 0;

	stClick = 0;
	ftClick++;

	if (ftClick == 1)
	{
		if (FirstTabActive == 0)
		{
			FirstTabActive = 1;
			SecondTabActive = 0;
		}

	}

	return FReply::Handled();
}

FReply SMySlateTabWidget::SecondTabClicked()
{
	TabIndex = 1;

	ftClick = 0;
	stClick++;

	if (stClick == 1)
	{
		if (SecondTabActive == 0)
		{
			FirstTabActive = 0;
			SecondTabActive = 1;
		}

	}

	return FReply::Handled();
}