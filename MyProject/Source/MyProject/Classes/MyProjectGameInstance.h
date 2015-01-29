// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyProject.h"
#include "MyProjectGameInstance.generated.h"

class MyAppFrame;

UCLASS(config=Game)
class UMyProjectGameInstance : public UGameInstance
{
public:
	GENERATED_UCLASS_BODY()

protected:
	MyAppFrame* m_myAppFrame;

public:
	virtual void Init() override;
};


