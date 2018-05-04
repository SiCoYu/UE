#pragma once

#include "UObject/Object.h"
#include "MyBluePrintBase.generated.h"

// ���� BluePrint �ǲ��Ҳ�����
//UCLASS(config = Game)
// �������ܲ��ҵ�
UCLASS(Blueprintable)
class UMyBluePrintBase : public UObject
{
	GENERATED_BODY()

public:
	UMyBluePrintBase(const FObjectInitializer& PCIP);
	void init();
	void dispose();
};