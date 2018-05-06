#pragma once 

#include "Widgets/SCompoundWidget.h"	// SCompoundWidget
#include "UObject/WeakObjectPtrTemplates.h"	// TWeakObjectPtr
#include "Input/Reply.h"		// FReply
#include "Widgets/SUserWidget.h"	// SUserWidget\FArguments

/**
* @url https://wiki.unrealengine.com/Slate_Tabs
*/

class AMyHUD;

class SMySlateTabWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SMySlateTabWidget)
	{}
	/*See private declaration of OwnerHUD below.*/
	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)
	/** The visual style of the button */
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	FReply FirstTabClicked();
	FReply SecondTabClicked();

	const FSlateBrush* GetFirstImageBrush() const;
	const FSlateBrush* GetSecondImageBrush() const;

private:
	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	int32 TabIndex;

	int32 GetCurrentTabIndex() const
	{
		return TabIndex;
	}
};