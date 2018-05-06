#include "MyProject.h"
#include "SlateLog.h"

// error C2248 : 'SSlateWidget::SSlateWidget' : cannot access private member declared in class 'SSlateWidget'
//SSlateLog::SSlateLog()
//{
	//static ConstructorHelpers::FClassFinder<UUserWidget> BigFontOb(TEXT("/Game/Blueprints/NewWidgetBlueprint"));

	//if (BigFontOb.Class != NULL)
	//{
	//	WidgetClass = BigFontOb.Class;
	//	UUserWidget* PawnToFit = WidgetClass->GetDefaultObject<UUserWidget>();
	//}
//}

void SSlateLog::Construct(const FArguments& InArgs)
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> BigFontOb(TEXT("/Game/Blueprints/NewWidgetBlueprint"));

	//if (BigFontOb.Class != NULL)
	//{
	//	WidgetClass = BigFontOb.Class;
	//	UUserWidget* PawnToFit = WidgetClass->GetDefaultObject<UUserWidget>();
	//}

	ChildSlot
	.VAlign(VAlign_Center)
	.HAlign(HAlign_Center)
	[					
		SNew( SVerticalBox )
		+SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		.Padding(20.0f)
		[
			SNew( SHorizontalBox)
			+SHorizontalBox::Slot()			
			.AutoWidth()
			.Padding(20.0f)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew( SButton )
				.ContentPadding(100)
				.Text(InArgs._MessageText)			
			]
		]			
	];
}