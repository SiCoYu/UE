#pragma once

#include "UObject/Object.h"	// UObject
#include "Delegates/DelegateCombinations.h"		// DECLARE_DELEGATE_ThreeParams
#include "MyObjectDelegate.generated.h"

// 定义一个 Delegate 类型
DECLARE_DELEGATE_ThreeParams(UMyObjectCommonDelegate, int, int, bool);

/**
 * @brief Delegate
 */

UCLASS(config = Game)
class UMyObjectDelegate : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UMyObjectCommonDelegate MyObjectCommonDelegate;

public:
	void handle(int aaa, int bbb, bool ccc);
};