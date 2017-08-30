#pragma once

#include "PlatformDefine.h"

#ifdef MY_WITH_EDITOR

#include "Editor/EditorEngine.h"		// class UNREALED_API UEditorEngine : public UEngine
#include "MyEditorEngineBase.generated.h"

UCLASS(config = Engine, transient)
class UMyEditorEngineBase : public UEditorEngine
{
	// û�����д��룬����ע���������ű�
	GENERATED_BODY()

public:
	UMyEditorEngineBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

#endif