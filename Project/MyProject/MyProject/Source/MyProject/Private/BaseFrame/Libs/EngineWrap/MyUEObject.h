#pragma once

#include "MyProject.h"
#include "MyUEObject.generated.h"

/**
 * @brief �̳� UObject �Ļ��࣬�ն������� NULL ����Ҫ�� nullptr �������ҵ�
 */
UCLASS(config = Game)
class UMyUEObject : public UObject
{
	GENERATED_BODY()

public:
	UMyUEObject(const FObjectInitializer& ObjectInitializer);
};