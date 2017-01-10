// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IMyPlugin.h"

/**
 https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins
 Note Please note that this article is not up to date and you may run into problems trying to get a working Plugin. If you just want to get an example Plugin with the current syntax to play around, look into your Unreal Engine Source Code at the path Engine/Plugins/Developer and checkout BlankPlugin. You can also just create an empty plugin by opening the Plugin Menu in the UE4Editor (Edit -> Plugins) and pressing "New Plugin". 
 You should also be aware of the Category. It provides a way for you to filter your plugins by type, developer or whatever you choose. Each sub category is separated by a period character. Above, Bobs.Content becomes Bobs > Content in the plugin listing in the editor, as shows in Figure 1, above.
 */

class FMyPluginModule : public IMyPlugin
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool IsThisNumber42(int32 num) override;
};