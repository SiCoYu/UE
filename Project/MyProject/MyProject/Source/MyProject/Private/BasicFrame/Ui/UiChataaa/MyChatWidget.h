// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyHUD.h"
#include "SlateBasics.h"

/**
 * @url https://wiki.unrealengine.com/Slate,_Simple_C%2B%2B_Chat_System
 */

class ITableRow;
struct FSChatMsg;
class STableViewBase;
class SVerticalBox;
class SEditableText;
class MyHUD;

template <typename ItemType>
class SListView;

class SMyChatWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SMyChatWidget) : _OwnerHUD() {} // the OwnerHUD var is passed to the widget so the owner can be set.

	SLATE_ARGUMENT(TWeakObjectPtr<class AMyHUD>, OwnerHUD)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	TSharedRef<class ITableRow> OnGenerateRowForList(TSharedPtr<struct FSChatMsg> Item, const TSharedRef<class STableViewBase>& OwnerTable); // the function that is called for each chat element to be displayed in the chatbox
	TArray<TSharedPtr<struct FSChatMsg>> Items; // array of all the current items in this players chat box
	TSharedPtr<class SListView< TSharedPtr<struct FSChatMsg> > > ListViewWidget; // the acutall widgets for each chat element

	const FSlateFontInfo fontinfo = FSlateFontInfo(FPaths::EngineContentDir() / TEXT("UI/Fonts/Comfortaa-Regular.ttf"), 15); // Font, Font Size  for the chatbox

	TWeakObjectPtr<class AMyHUD> OwnerHUD;

	TSharedPtr<class SVerticalBox> ChatBox;
	TSharedPtr<class SEditableText> ChatInput;

	void OnChatTextChanged(const FText& InText);
	void OnChatTextCommitted(const FText& InText, ETextCommit::Type CommitMethod);

	void AddMessage(const FSChatMsg& newmessage); // the final stage, this function takes the input and does the final placement in the chatbox

	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime); // The full widget ticks and deletes messages
};