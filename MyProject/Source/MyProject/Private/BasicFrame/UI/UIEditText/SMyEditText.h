#pragma once

//Slate
#include "Slate.h"

/**
 * @URL https://wiki.unrealengine.com/Slate,_Edit_Text_Widget,_Custom_Rendering_%26_Any_TrueTypeFont
 */

//~~~ Forward Declarations ~~~
class AYourHUD;



class SMyEditText : public SCompoundWidget
{
	//Slate Init
public:
	SLATE_BEGIN_ARGS(SVictoryEditText) : _JoyHUD() //, _bKeepVisible(false)
	{}

	SLATE_ARGUMENT(TWeakObjectPtr<AYourHUD>, JoyHUD)

		SLATE_END_ARGS()

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~
		//  HUD
		//~~~~~~~~
public:
	//HUD that owns this
	TWeakObjectPtr<class AYourHUD> JoyHUD;

	//~~~~~~~~
	//Components
	//~~~~~~~~
public:
	//The edit text widget. 
	TSharedPtr< SEditableText > ChatInput;

	//How the Edit Text is actually displayed
	TSharedPtr< STextBlock > ChatDisplay;

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
			ChatInput->CopySelectedTextToClipboard();
		}
	}
	FORCEINLINE void PasteFromClipboard()
	{
		if (ChatInput.IsValid())
		{
			ChatInput->PasteTextFromClipboard();
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
	virtual FReply OnKeyboardFocusReceived(const FGeometry& MyGeometry, const FKeyboardFocusEvent& InKeyboardFocusEvent) OVERRIDE;

	//~~~ Key Down  ~~~  		
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyboardEvent& InKeyboardEvent) OVERRIDE;

	//~~~ Mouse Down  ~~~
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) OVERRIDE;



	//Slate Base
public:

	//Constructor
	void Construct(const FArguments& InArgs);

	//As Widget
	TSharedRef<class SWidget> AsWidget();

	//~~~ Tick ~~~ 
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

};