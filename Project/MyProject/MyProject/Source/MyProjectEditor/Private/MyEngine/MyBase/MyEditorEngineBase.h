#pragma once

#include "PlatformDefine.h"

#ifdef MY_WITH_EDITOR

#include "Editor/EditorEngine.h"		// class UNREALED_API UEditorEngine : public UEngine
#include "MyEditorEngineBase.generated.h"

UCLASS(config = Engine, transient)
class UMyEditorEngineBase : public UEditorEngine
{

};

#endif