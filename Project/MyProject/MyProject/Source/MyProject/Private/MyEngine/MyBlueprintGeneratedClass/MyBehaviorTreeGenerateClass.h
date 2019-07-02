#pragma once

#include "PlatformDefine.h"

class UBehaviorTree;

/**
 * @brief 只有资源，没有脚本，因此 UBehaviorTree 不是继承自 UBlueprintGeneratedClass
 */
class MyBehaviorTreeGenerateClass
{
protected:
	UBehaviorTree* mBlueprint;
};