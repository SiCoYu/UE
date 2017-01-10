// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "MyPluginWinStyle.h"

class FMyPluginWinCommands : public TCommands<FMyPluginWinCommands>
{
public:

	FMyPluginWinCommands()
		: TCommands<FMyPluginWinCommands>(TEXT("MyPluginWin"), NSLOCTEXT("Contexts", "MyPluginWin", "MyPluginWin Plugin"), NAME_None, FMyPluginWinStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};