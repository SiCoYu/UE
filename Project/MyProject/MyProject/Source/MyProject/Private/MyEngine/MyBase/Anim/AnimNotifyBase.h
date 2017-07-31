#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"	// UAnimNotify
#include "AnimNotifyBase.generated.h"

/**
 * @brief MyAnimInstanceBase
 * @ref ue4中动画通知的几种方式: http://blog.csdn.net/yangxuan0261/article/details/52097917
 * @ref ue4-骨骼动画相关(换装、重定向、曲线、变形): http://blog.csdn.net/yangxuan0261/article/details/54631067
 * @ref ue4-混合动画及动画状态机: http://blog.csdn.net/yangxuan0261/article/details/54630949
 * @brief 虚幻4 捏脸和换装系统实现: http://www.chinaar.com/UE4/1817.html ,Demo下载 链接：http://pan.baidu.com/s/1eQRwhGI 密码：5ji2
 */

UCLASS()
class UAnimNotifyBase : public UAnimNotify
{
	GENERATED_UCLASS_BODY()
};