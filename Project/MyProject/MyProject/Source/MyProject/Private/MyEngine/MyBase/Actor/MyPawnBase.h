#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawnBase.generated.h"

/**
 * @brief �̳��� APawn �����л������������ԣ������ڿ��л�����
 */
UCLASS(config = Game)
class AMyPawnBase : public APawn
{
	GENERATED_BODY()

public:
	AMyPawnBase();
	virtual void BeginPlay() override;
};
