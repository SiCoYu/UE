#pragma once

//fatal error C1083: Cannot open include file: 'PlatformDefine.h': No such file or directory
//#include "PlatformDefine.h"

// UE4 4.17: error : UCLASS inside this preprocessor block will be skipped
// #ifdef MY_WITH_EDITOR

#include "Editor/UnrealEdEngine.h"		// class UNREALED_API UUnrealEdEngine : public UEditorEngine, public FNotifyHook
#include "MyUnrealEdEngineBase.generated.h"

UCLASS(config = Engine, transient)
class UMyUnrealEdEngineBase : public UUnrealEdEngine
{
	// û�����д��룬����ע���������ű�
	GENERATED_BODY()

public:
	UMyUnrealEdEngineBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

//#endif