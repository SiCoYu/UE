#pragma once

#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
// https://wiki.unrealengine.com/Slate,_Edit_Text_Widget,_Custom_Rendering_%26_Any_TrueTypeFont
//#include "SMyEditText.h"
#include "MyHUD.generated.h"

class SMyDialog;
class MyUILoadStyleWidget;
class SMyEditText;

UCLASS()
class AMyHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

public:
	/** Main HUD update loop. */
	virtual void DrawHUD() override;

public:
	//UFUNCTION(BlueprintCallable, Category = "Button")
	//FReply OnConfirmGeneric();

	UFUNCTION(BlueprintCallable, Category = "Button")
	void OnConfirmGeneric();

protected:
	/** kills background icon. */
	UPROPERTY()
	FCanvasIcon KillsBg;

	/** Large font - used for ammo display etc. */
	UPROPERTY()
	UFont* BigFont;

	/** Darker HUD color. */
	FColor HUDDark;

	TSharedPtr<SMyDialog>			DialogWidget;
	//UUserWidget* NewWidget;

	// https://wiki.unrealengine.com/Survival_Sample_Game:_Section_4
public:
	/* An event hook to call HUD text events to display in the HUD. Blueprint HUD class must implement how to deal with this event. */
	UFUNCTION(BlueprintImplementableEvent, Category = "HUDEvents")
	void MessageReceived(const FString& TextMessage);

	// https://wiki.unrealengine.com/Slate,_Simple_C%2B%2B_Chat_System
public:
	TSharedPtr<class SMyChatWidget> MyUIWidget; // Reference to the main chat widget

	APlayerController* MyPC;

	UFUNCTION(BlueprintCallable, Category = "User")
	void AddMessageBP(const int32 Type, const FString& Username, const FString& Text, const bool Replicate); // A Blueprint function you can use to place messages in the chat box during runtime

protected:
	virtual void PostInitializeComponents() override; // All game elements are created, add our chat box

	void DrawHUD_ChatSystem(); // The HUD is drawn on our screen

	// https://wiki.unrealengine.com/Slate,_Loading_Styles_%26_Resources
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called as soon as game starts, create SCompoundWidget and give Viewport access
	virtual void BeginPlay() override;
protected:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Reference to SCompoundWidget
	TSharedPtr<class MyUILoadStyleWidget> mMyUILoadStyleWidget;

	// https://wiki.unrealengine.com/Slate,_Edit_Text_Widget,_Custom_Rendering_%26_Any_TrueTypeFont
	// error : BlueprintReadOnly should not be used on private members
//private:
public:
	/** Default True Type Font. This should be the path off of Content that leads to your chosen TTF. Copy paste .ttf files from Windows/Fonts. Path should not include "Content".  Ex: "TTF/comicbd.ttf" */
	// error : BlueprintReadOnly should not be used on private members
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = VictoryChat)
	FString ChatFontTTF;
	// error : BlueprintReadWrite should not be used on private members
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VictoryChat)
	//FString ChatFontTTF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VictoryChat)
	int32 ChatInputFontSize;

	/** Set a new .ttf for chat text! This should be the path off of Content that leads to your chosen TTF. Copy paste .ttf files from Windows/Fonts. Path should not include "Content".  Ex: "TTF/comicbd.ttf" */
	UFUNCTION(BlueprintCallable, Category = VictoryChat)
	void SetChatFont(FString NewFontPath);

	//Slate Core
public:
	TSharedPtr<class SMyEditText> VictoryChat;

	void JoyInit_VictoryChat();

	void DrawHUD_EditText();
};
