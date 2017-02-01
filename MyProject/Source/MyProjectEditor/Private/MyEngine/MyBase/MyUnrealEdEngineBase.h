#pragma once

#include "PlatformDefine.h"

#ifdef MY_WITH_EDITOR

#include "Editor/UnrealEdEngine.h"		// class UNREALED_API UUnrealEdEngine : public UEditorEngine, public FNotifyHook
#include "MyUnrealEdEngineBase.generated.h"

UCLASS(config = Engine, transient)
class UMyUnrealEdEngineBase : public UUnrealEdEngine
{

};

#endif