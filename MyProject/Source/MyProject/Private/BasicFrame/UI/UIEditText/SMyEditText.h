#pragma once

// including Slate.h is deprecated. Please include SlateBasics.h and then individual widget headers instead.
//Slate
//#include "Slate.h"
#include "SlateBasics.h"
#include "Widgets/Input/SEditableText.h"	// SEditableText
#include "Widgets/Text/STextBlock.h"		// STextBlock
#include "Widgets/SCompoundWidget.h"

/**
 * @URL https://wiki.unrealengine.com/Slate,_Edit_Text_Widget,_Custom_Rendering_%26_Any_TrueTypeFont
 */

//~~~ Forward Declarations ~~~
class AMyHUD;

class SMyEditText : public SCompoundWidget
{
	//Slate Init
public:
	SLATE_BEGIN_ARGS(SMyEditText) : _JoyHUD() //, _bKeepVisible(false)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, JoyHUD)

	SLATE_END_ARGS()

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//~~~~~~~~
	//  HUD
	//~~~~~~~~

public:
	//HUD that owns this
	TWeakObjectPtr<class AMyHUD> JoyHUD;

	//~~~~~~~~
	//Components
	//~~~~~~~~
public:
	//The edit text widget. 
	TSharedPtr<class SEditableText> ChatInput;

	//How the Edit Text is actually displayed
	TSharedPtr<class STextBlock> ChatDisplay;

	//~~~~~~~~~~~~~~~~~
	//  Chat Visibility
	//~~~~~~~~~~~~~~~~~
public:
	void SetShowChat(bool MakeVisible);


	//~~~~~~~~~~~~~~~~~~~~~
	//  Copy/Paste Text 
	//~~~~~~~~~~~~~~~~~~~~~
public:
	FORCEINLINE void CopyToClipboard()
	{
		if (ChatInput.IsValid())
		{
			// TODO:
			//ChatInput->CopySelectedTextToClipboard();
			FText text = ChatInput->GetSelectedText();
		}
	}
	FORCEINLINE void PasteFromClipboard()
	{
		if (ChatInput.IsValid())
		{
			// TODO:
			//ChatInput->PasteTextFromClipboard();
		}
	}

	//~~~~~~~~~~~~~~~~~
	// Chat Text Entry 
	//~~~~~~~~~~~~~~~~~
public:

	//Set Slate UI Mode, Capture User Keyboard Input
	void SetSlateUIMode(bool EnterSlateUI);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Delegate called when the text is commited.

	// @param	InText			The committed text.
	// @Param	InCommitInfo	The type of commit (eg. Pressed enter, changed focus) 
	void OnChatTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//	     Text Changed Delegate!
	void OnChatTextChanged(const FText& InText);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//~~~~~~~~~~~~~~~~~
	//  Base Input
	//~~~~~~~~~~~~~~~~~
	//SWidget.h
public:
	//~~~ Keyboard Focused ~~~
	// error C3646: 'EMIT_DEPRECATED_WARNING_MESSAGE': unknown override specifier
	//virtual FReply OnKeyboardFocusReceived(const FGeometry& MyGeometry, const FKeyboardFocusEvent& InKeyboardFocusEvent) OVERRIDE;
	virtual FReply OnKeyboardFocusReceived(const FGeometry& MyGeometry, const FKeyboardFocusEvent& InKeyboardFocusEvent) override;

	//~~~ Key Down  ~~~  		
	//virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyboardEvent& InKeyboardEvent) override;
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyboardEvent) override;

	//~~~ Mouse Down  ~~~
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;



	//Slate Base
public:

	//Constructor
	void Construct(const FArguments& InArgs);

	//As Widget
	TSharedRef<class SWidget> AsWidget();

	//~~~ Tick ~~~ 
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

};