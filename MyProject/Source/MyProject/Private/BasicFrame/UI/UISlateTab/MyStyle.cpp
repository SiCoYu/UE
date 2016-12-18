#include "MyProject.h"
#include "MyStyle.h"

#include "TabbedView.h"
#include "MyStyle.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "SlateStyle.h"

#define IMAGE_BRUSH(RelativePath, ...)	FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> CreateStyle()
{
	TSharedPtr<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("PreloadStyle"));
	Style->SetContentRoot(FPaths::GameContentDir() / "Slate");

	Style->Set("tab_normal", new IMAGE_BRUSH("tab_normal", FVector2D(256, 64)));
	Style->Set("tab_active", new IMAGE_BRUSH("tab_active", FVector2D(256, 64)));

	return Style;
}

#undef IMAGE_BRUSH


TSharedPtr<ISlateStyle> FMyStyle::StylePtr = NULL;

void FMyStyle::Initialize()
{
	if (!StylePtr.IsValid())
	{
		StylePtr = CreateStyle();
		FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
	}
}

void FMyStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
	ensure(StylePtr.IsUnique());
	StylePtr.Reset();
}

const ISlateStyle& FMyStyle::Get()
{
	return *StylePtr;
}