#include "MyProject.h"
#include "UI/MyHUD.h"

AMyHUD::AMyHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas == nullptr)
	{
		return;
	}

	//FString Text = LOCTEXT("WaitingForRespawn", "WAITING FOR RESPAWN").ToString();
	//FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	//TextItem.EnableShadow(FLinearColor::Black);
	//TextItem.Text = FText::FromString(Text);
	//TextItem.Scale = FVector2D(1.0f, 1.0f);
	//TextItem.FontRenderInfo = ShadowedFont;
	//TextItem.SetColor(FLinearColor(0.75f, 0.125f, 0.125f, 1.0f));
	//Canvas->DrawItem(TextItem);
}