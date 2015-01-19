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

	static ConstructorHelpers::FClassFinder<UUserWidget> aaa(TEXT("/Game/Blueprints/NewWidgetBlueprint"));

	if (aaa.Class != NULL)
	{
		TSubclassOf<class UUserWidget> WidgetClass = aaa.Class;
		UUserWidget* PawnToFit = WidgetClass->GetDefaultObject<UUserWidget>();

		NewWidget = Cast<UUserWidget>(StaticConstructObject(*WidgetClass));
		//NewWidget->AddToViewport();
	}
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
		DialogWidget = SNew(SMyDialog)
			.MessageText("asdfasdasdfadsf");

		SMyDialog::FArguments aaa;
		aaa.MessageText("asdfasdasdfadsf");
		DialogWidget->Construct(aaa);

		//GEngine->GameViewport->AddViewportWidgetContent(DialogWidget.ToSharedRef());

		//NewWidget->AddToViewport();

		TSharedPtr<SWidget> OutUserSlateWidget;
		TSharedRef<SWidget> RootWidget = NewWidget->MakeViewportWidget(OutUserSlateWidget);
		GEngine->GameViewport->AddViewportWidgetContent(RootWidget);
		//UWidget* bbb = NewWidget->GetContentForSlot("aaa");
		TSharedPtr<SButton> bbb = MakeShareable((SButton*)(NewWidget->GetSlateWidgetFromName("Button_19").Get()));
		bbb->SetOnClicked(FOnClicked::CreateRaw(this, &AMyHUD::OnConfirmGeneric));
	}

	//NewWidget->AddToViewport();
}

FReply AMyHUD::OnConfirmGeneric()
{
	return FReply::Handled();
}