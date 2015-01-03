// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MyProject.h"
#include "MyDialog.h"

SMyDialog::SMyDialog()
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> BigFontOb(TEXT("/Game/Blueprints/NewWidgetBlueprint"));

	//if (BigFontOb.Class != NULL)
	//{
	//	WidgetClass = BigFontOb.Class;
	//	UUserWidget* PawnToFit = WidgetClass->GetDefaultObject<UUserWidget>();
	//}
}

void SMyDialog::Construct( const FArguments& InArgs )
{
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