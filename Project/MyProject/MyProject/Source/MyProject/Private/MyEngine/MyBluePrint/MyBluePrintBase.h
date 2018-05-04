#pragma once

#include "UObject/Object.h"
#include "MyBluePrintBase.generated.h"

// 这样 BluePrint 是查找不到的
//UCLASS(config = Game)
// 这样才能查找到
UCLASS(Blueprintable)
class UMyBluePrintBase : public UObject
{
	GENERATED_BODY()

public:
	UMyBluePrintBase(const FObjectInitializer& PCIP);
	void init();
	void dispose();
};