#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawnBase.generated.h"

/**
 * @brief 继承于 APawn 不会有基本的物理属性，例如在空中会下落
 */
UCLASS(config = Game)
class AMyPawnBase : public APawn
{
	GENERATED_BODY()

public:
	AMyPawnBase();
	virtual void BeginPlay() override;
};
