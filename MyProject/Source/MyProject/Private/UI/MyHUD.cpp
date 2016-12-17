#include "MyProject.h"
#include "UI/MyHUD.h"

#include "CanvasItem.h"
#include "MyDialog.h"
//#include "EngineGlobals.h"		// GEngine
#include "Engine.h"

#define LOCTEXT_NAMESPACE "MyProject.HUD"

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/UI/HUD/Roboto51"));
	BigFont = BigFontOb.Object;
	HUDDark = FColor(110, 124, 131, 255);
	AHUD* aa = dynamic_cast<AHUD*>(this);

	//static ConstructorHelpers::FClassFinder<UUserWidget> aaa(TEXT("/Game/Blueprints/NewWidgetBlueprint"));

	//if (aaa.Class != NULL)
	//{
	//	TSubclassOf<class UUserWidget> WidgetClass = aaa.Class;
	//	UUserWidget* PawnToFit = WidgetClass->GetDefaultObject<UUserWidget>();

		//NewWidget = Cast<UUserWidget>(StaticConstructObject(*WidgetClass));
		//NewWidget->AddToViewport();
	//}
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	if (Canvas == nullptr)
	{
		return;
	}

	FString Text = LOCTEXT("WaitingForRespawn", "WAITING FOR RESPAWN").ToString();
	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow(FLinearColor::Black);
	TextItem.Text = FText::FromString(Text);
	TextItem.Scale = FVector2D(1.0f, 1.0f);
	//TextItem.FontRenderInfo = ShadowedFont;
	TextItem.SetColor(FLinearColor(0.75f, 0.125f, 0.125f, 1.0f));
	Canvas->DrawItem(TextItem);

	if (!DialogWidget.IsValid())
	{
		// warning C4996: 'SMyDialog::FArguments::MessageText': Passing text to Slate as FString is deprecated, please use FText instead (likely via a LOCTEXT). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
		//DialogWidget = SNew(SMyDialog)
		//	.MessageText("asdfasdasdfadsf");

		DialogWidget = SNew(SMyDialog)
			.MessageText(LOCTEXT("MyHUB", "asdfasdasdfadsf"));

		SMyDialog::FArguments aaa;
		//aaa.MessageText("asdfasdasdfadsf");
		aaa.MessageText(LOCTEXT("MyHUB", "asdfasdasdfadsf"));
		DialogWidget->Construct(aaa);

		//GEngine->GameViewport->AddViewportWidgetContent(DialogWidget.ToSharedRef());

		//NewWidget->AddToViewport();

		//TSharedPtr<SWidget> OutUserSlateWidget;
		//TSharedRef<SWidget> RootWidget = NewWidget->MakeViewportWidget(OutUserSlateWidget);
		//GEngine->GameViewport->AddViewportWidgetContent(RootWidget);
		//UWidget* bbb = NewWidget->GetContentForSlot("aaa");
		
		//TSharedPtr<SButton> bbb = MakeShareable((SButton*)(NewWidget->GetSlateWidgetFromName("Button_16").Get()));

		//UButton* ccc = (UButton*)NewWidget->GetWidgetFromName("Button_14");
		//FWeakObjectPtr fff(this);
		//TScriptDelegate<FWeakObjectPtr> ddd;
		//TScriptDelegate<AMyHUD> ddd;

		//ddd.BindUFunction((UObject *)this, "OnConfirmGeneric");
		//ccc->OnClicked.Add(ddd);

		//bbb->SetOnClicked(FOnClicked::CreateRaw(this, &AMyHUD::OnConfirmGeneric));
		//bbb->SetOnClicked(FOnClicked::CreateSP(this, &AMyHUD::OnConfirmGeneric));
		//bbb->SetOnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, OnConfirmGeneric));

		//FOnClicked InOnClicked = FOnClicked::CreateUObject(this, &AMyHUD::OnConfirmGeneric);
		//bbb->SetOnClicked(InOnClicked);
	}

	//NewWidget->AddToViewport();

	this->DrawHUD_ChatSystem();
}

//FReply AMyHUD::OnConfirmGeneric()
void AMyHUD::OnConfirmGeneric()
{
	//return FReply::Handled();
}

void AMyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GEngine && GEngine->GameViewport) // make sure our screen is ready for the widget
	{
		SAssignNew(MyUIWidget, SMyChatWidget).OwnerHUD(this); // add the widget and assign it to the var
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));
	}
}

void AMyHUD::DrawHUD_ChatSystem()
{
	if (!MyPC)
	{
		MyPC = GetOwningPlayerController();
		AddMessageBP(2, TEXT(""), TEXT("Welcome. Press Enter to chat."), false); // random Welcome message shown to the local player. To be deleted. note type 2 is system message and username is blank
		return;
	}

	if (MyPC->WasInputKeyJustPressed(EKeys::Enter))
		if (MyUIWidget.IsValid() && MyUIWidget->ChatInput.IsValid())
			FSlateApplication::Get().SetKeyboardFocus(MyUIWidget->ChatInput); // When the user presses Enter he will focus his keypresses on the chat input bar
}

void AMyHUD::AddMessageBP(const int32 Type, const FString& Username, const FString& Text, const bool Replicate)
{
	if (!MyPC || !MyUIWidget.IsValid())
		return;

	FSChatMsg newmessage;
	newmessage.Init(Type, FText::FromString(Username), FText::FromString(Text)); // initialize our struct and prep the message
	if (newmessage.Type > 0)
		if (Replicate)
		{
			AMyPlayerState* MyPS = Cast<AMyPlayerState>(MyPC->PlayerState);
			if (MyPS)
				MyPS->UserChatRPC(newmessage); // Send the complete chat message to the PlayerState so it can be replicated then displayed
		}
		else
			MyUIWidget->AddMessage(newmessage); // Send a local message to this client only, no one else receives it
}

void AMyHUD::BeginPlay()
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Create a SMyUIWidget on heap referenced by MyUIWidget pointer member
	SAssignNew(MyUIWidget, SMyUIWidget).OwnerHUD(this);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pass our viewport a weak reference to our widget, will not increment refcount
	if (GEngine->IsValidLowLevel())
		GEngine->GameViewport->
		AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));

	if (MyUIWidget.IsValid())
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/////Set widget's properties as visibile (sets child widget's properties recurisvely)
		MyUIWidget->SetVisibility(EVisibility::Visible);
	}
}