#pragma once

#include "MyProject.h"
#include "MyUEObject.generated.h"

/**
 * @brief 继承 UObject 的基类，空对象设置 NULL ，不要用 nullptr ，否则会挂掉
 */
UCLASS(config = Game)
class UMyUEObject : public UObject
{
	GENERATED_BODY()

public:
	UMyUEObject(const FObjectInitializer& ObjectInitializer);
};