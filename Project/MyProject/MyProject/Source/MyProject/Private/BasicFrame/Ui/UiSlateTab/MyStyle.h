#pragma once

/**
 * @url https://wiki.unrealengine.com/Slate_Tabs
 */

class FMyStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

	static TSharedPtr<class ISlateStyle> StylePtr;

};