// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "ScriptPluginExport.generated.h"

struct lua_State;

/**
* @brief ScriptPluginExport, UCLASS ���ܵ����� DLL����˶���һ��
*/
// TODO: UCLASS() ����뱨��
UCLASS(config = Game)
class SCRIPTPLUGIN_API UScriptPluginExport : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	static void initPlugin(lua_State* luaState);
};