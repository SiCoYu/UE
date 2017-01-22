#pragma once

#include "Math/Rotator.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstanceBase.generated.h"

/**
 * @brief MyAnimInstanceBase
 * @ref ue4�ж���֪ͨ�ļ��ַ�ʽ: http://blog.csdn.net/yangxuan0261/article/details/52097917
 * @ref ue4-�����������(��װ���ض������ߡ�����): http://blog.csdn.net/yangxuan0261/article/details/54631067
 * @ref ue4-��϶���������״̬��: http://blog.csdn.net/yangxuan0261/article/details/54630949
 * @brief ���4 �����ͻ�װϵͳʵ��: http://www.chinaar.com/UE4/1817.html ,Demo���� ���ӣ�http://pan.baidu.com/s/1eQRwhGI ���룺5ji2
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
	// ���ȣ�animation bp�����Ǽ̳��Զ����AnimInstance
	// Ȼ���½�����֪ͨAnimNotify_Begin��AnimNotify_End
	// �������������������AnimNotify_XXX����Ϊ������Ĵ����������ƥ���
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