// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SMyDialog : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS( SMyDialog )
	{}

	SLATE_TEXT_ARGUMENT(MessageText)

	SLATE_END_ARGS()	

	void Construct(const FArguments& InArgs);
};
