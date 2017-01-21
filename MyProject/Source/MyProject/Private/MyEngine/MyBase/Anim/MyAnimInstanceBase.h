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