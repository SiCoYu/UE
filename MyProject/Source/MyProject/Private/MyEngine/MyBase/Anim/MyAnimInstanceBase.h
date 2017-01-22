#pragma once

#include "Math/Rotator.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstanceBase.generated.h"

/**
 * @brief MyAnimInstanceBase
 * @ref ue4中动画通知的几种方式: http://blog.csdn.net/yangxuan0261/article/details/52097917
 * @ref ue4-骨骼动画相关(换装、重定向、曲线、变形): http://blog.csdn.net/yangxuan0261/article/details/54631067
 * @ref ue4-混合动画及动画状态机: http://blog.csdn.net/yangxuan0261/article/details/54630949
 * @brief 虚幻4 捏脸和换装系统实现: http://www.chinaar.com/UE4/1817.html ,Demo下载 链接：http://pan.baidu.com/s/1eQRwhGI 密码：5ji2
 */

UCLASS(config = Game)
class UMyAnimInstanceBase : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
	FRotator NeckSpring;

public:
	UMyAnimInstanceBase();

public:
	void testA();

public:
	AActor* mOwnerActor;

	/** Is Moving */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	bool IsMoving;

	//init and tick
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// http://blog.csdn.net/yangxuan0261/article/details/52097917
	// 首先，animation bp必须是继承自定义的AnimInstance
	// 然后新建两个通知AnimNotify_Begin和AnimNotify_End
	// 方法的命名规则必须是AnimNotify_XXX，因为引擎里的代码就是这样匹配的
public:
	UFUNCTION(BlueprintCallable, Category = "MyAnim")
	bool IsInMoving();

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
	AActor* GetOwnerActor();

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
	void AnimNotify_Begin(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "MyAnim")
	void AnimNotify_End(UAnimNotify* Notify);
};