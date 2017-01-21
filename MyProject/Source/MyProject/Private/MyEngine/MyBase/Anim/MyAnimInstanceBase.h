#pragma once

#include "Math/Rotator.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstanceBase.generated.h"

/**
 * @brief MyAnimInstanceBase
 * @ref ue4中动画通知的几种方式
 * @url http://blog.csdn.net/yangxuan0261/article/details/52097917
 * @ref ue4-骨骼动画相关(换装、重定向、曲线、变形) 
 * @url http://blog.csdn.net/yangxuan0261/article/details/54631067
 * @ref ue4-混合动画及动画状态机 
 * @url http://blog.csdn.net/yangxuan0261/article/details/54630949
 */

UCLASS(config = Game)
class UMyAnimInstanceBase : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	FRotator NeckSpring;

public:
	void testA();

public:
	APawn * OwningPawn;

	/** Is Moving */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool IsMoving;

	//init and tick
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};