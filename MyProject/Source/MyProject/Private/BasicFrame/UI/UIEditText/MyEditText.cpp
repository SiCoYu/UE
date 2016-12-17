#include "MyProject.h"
#include "MyEditText.h"

void SMyEditText::Construct(const FArguments& InArgs)
{
	JoyHUD = InArgs._JoyHUD;

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		//~~~~~~~~~~~~~~~~~~~~
		//  Being Slate Construct Block
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		[

			//~~~ Chat Input ~~~
			SAssignNew(ChatInput, SEditableText)

			//Function to call when text is entered
		.OnTextCommitted(this, &SMyEditText::OnChatTextCommitted)


		//Function to call when text is changed
		.OnTextChanged(this, &SMyEditText::OnChatTextChanged)


		//Stay and possibly enter multiple lines
		.ClearKeyboardFocusOnCommit(false)

		//Optional
		//.MinDesiredWidth(500)	

		.Text(FText::FromString("Victory!"))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 24))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 0))    //<~~~

													  //Chat input itself is hidden, display used instead
													  //		for the shadowing, and as a demonstration
													  //		of accessing the input text and displaying it elsewhere
													  //			See Tick Function

		]
	+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		[
			SAssignNew(ChatDisplay, STextBlock)
			.Text(FText::FromString("Victory!!!!"))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 24))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-2, 2))
		]
		]; //End Slate Construct Block
		   //~~~~~~~~~~~~~~~~~~~~~~~~

}

//~~~~~~~~~~
//  Base 
//~~~~~~~~~~
TSharedRef<SWidget> SMyEditText::AsWidget()
{
	return SharedThis(this);
}

//~~~~~~~~~~~~~
// Base Input
//~~~~~~~~~~~~~
//Keyboard Focussed
//FReply SMyEditText::OnKeyboardFocusReceived(const FGeometry& MyGeometry, const FKeyboardFocusEvent& InKeyboardFocusEvent)
FReply SMyEditText::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	//Lock Mouse To Edit
	//  warning C4996: 'FReply::ReleaseJoystickCapture': FReply::ReleaseJoystickCapture() is deprecated, use FReply::ClearUserFocus() instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//return FReply::Handled().ReleaseMouseCapture().ReleaseJoystickCapture().LockMouseToWidget(SharedThis(this));
	return FReply::Handled().ReleaseMouseCapture().ClearUserFocus().LockMouseToWidget(SharedThis(this));
}

//~~~ Key Down ~~~
FReply SMyEditText::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyboardEvent)
{
	//Get Key Pressed
	const FKey VKey = InKeyboardEvent.GetKey();

	//ESC Pressed
	if (VKey == EKeys::Escape)
	{
		//Exit!
		SetSlateUIMode(false);
		return FReply::Handled();
	}

	if (InKeyboardEvent.IsControlDown())
	{
		if (!ChatInput.IsValid()) return FReply::Handled();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~

		//CTRL + V = Paste
		if (VKey == EKeys::V)
		{
			PasteFromClipboard();
		}
		//CTRL + C = Copy
		if (VKey == EKeys::C)
		{
			//Copy All
			FWindowsPlatformMisc::ClipboardCopy(*ChatInput->GetText().ToString());

			//or you can use the highlighting of text method
			//CopyToClipboard();
		}
	}
	return FReply::Handled();
}

//~~~ Mouse Down  ~~~
FReply SMyEditText::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//Get Key Pressed
	const FKey VKey = MouseEvent.GetEffectingButton();

	//LMB Pressed
	if (VKey == EKeys::LeftMouseButton)
	{
		//Exit!
		SetSlateUIMode(false);
		return FReply::Handled();
	}

	return FReply::Handled();
}

//~~~~~~~~~~~~~~~~
//   Show Chat
//~~~~~~~~~~~~~~~~
void SMyEditText::SetShowChat(bool MakeVisible)
{
	TAttribute<EVisibility> NewVisibility;
	if (MakeVisible)
	{
		NewVisibility = EVisibility::Visible;
		SetVisibility(NewVisibility);
		ChatInput->SetVisibility(NewVisibility);
		ChatDisplay->SetVisibility(NewVisibility);
	}
	else
	{
		NewVisibility = EVisibility::Hidden;
		SetVisibility(NewVisibility);
		ChatInput->SetVisibility(NewVisibility);
		ChatDisplay->SetVisibility(NewVisibility);
	}
}

//~~~~~~~~~~~~~~~~
// Chat Text Entered
//~~~~~~~~~~~~~~~~
void SMyEditText::OnChatTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo)
{
	if (InCommitInfo == ETextCommit::OnEnter)
	{
		if (!InText.IsEmpty())
		{
			if (ChatInput.IsValid())
			{
				// Add the string so we see it too (we will ignore our own strings in the receive function)
				//AddChatLine( InText.ToString() );

				// Clear the text
				ChatInput->SetText(FText());
			}
		}

		//Exit properly! Hides mouse and restores Viewport control
		SetSlateUIMode(false);
	}
}
//~~~~~~~~~~~~~~~~
// Chat Text Changed
//~~~~~~~~~~~~~~~~
void SMyEditText::OnChatTextChanged(const FText& InText)
{
	if (!ChatDisplay.IsValid()) 	return;
	if (!ChatInput.IsValid()) 		return;

	//~~~ Update The Chat Display! ~~~
	ChatDisplay->SetText(ChatInput->GetText().ToString() + FString(" "));

	//single space to fix letter clipping, not sure why its clipping.

}
//~~~~~~~~~~~~~~~~
//  Slate UI Mode
//~~~~~~~~~~~~~~~~
void SMyEditText::SetSlateUIMode(bool EnterSlateUI)
{
	if (EnterSlateUI)
	{
		// Enter UI mode
		FSlateApplication::Get().SetKeyboardFocus(SharedThis(this));

		if (ChatInput.IsValid())
		{
			FWidgetPath WidgetToFocusPath;

			//bool bFoundPath = FSlateApplication::Get().FindPathToWidget(FSlateApplication::Get().GetInteractiveTopLevelWindows(), ChatInput.ToSharedRef(), WidgetToFocusPath);
			bool bFoundPath = FSlateApplication::Get().FindPathToWidget(ChatInput.ToSharedRef(), WidgetToFocusPath);
			if (bFoundPath && WidgetToFocusPath.IsValid())
			{
				FSlateApplication::Get().SetKeyboardFocus(WidgetToFocusPath, EKeyboardFocusCause::SetDirectly);
			}
		}
	}
	else
	{
		// Exit UI mode
		FSlateApplication::Get().SetFocusToGameViewport();
	}
}
//~~~~~~~~~~~~~~~~
//	Tick
//~~~~~~~~~~~~~~~~
void SMyEditText::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	// Always tick the super.
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


}