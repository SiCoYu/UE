// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyProject.h"
#include "MyProjectGameInstance.generated.h"

class AppFrame;

UCLASS(config=Game)
class UMyProjectGameInstance : public UGameInstance
{
public:
	GENERATED_UCLASS_BODY()

protected:
	AppFrame* m_appFrame;

public:
	virtual void Init() override;
};


