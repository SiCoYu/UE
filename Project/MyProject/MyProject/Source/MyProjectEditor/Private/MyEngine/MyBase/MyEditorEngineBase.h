#pragma once

#include "PlatformDefine.h"

// UE4 4.17: error : UCLASS inside this preprocessor block will be skipped
//#ifdef MY_WITH_EDITOR

#include "Editor/EditorEngine.h"		// class UNREALED_API UEditorEngine : public UEngine
#include "MyEditorEngineBase.generated.h"

// error : UCLASS inside this preprocessor block will be skipped
UCLASS(config = Engine, transient)
class UMyEditorEngineBase : public UEditorEngine
{
	// û�����д��룬����ע���������ű�
	GENERATED_BODY()

public:
	UMyEditorEngineBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

//#endif