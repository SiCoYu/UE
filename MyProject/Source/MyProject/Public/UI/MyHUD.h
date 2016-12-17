#pragma once

#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class SMyDialog;
class MyUILoadStyleWidget;

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
	TSharedPtr<class MyUILoadStyleWidget> MyUIWidget;
};
