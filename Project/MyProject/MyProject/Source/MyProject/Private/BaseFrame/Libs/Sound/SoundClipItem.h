#pragma once

#include "SoundItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 直接加载声音文件
 */
class SoundClipItem : public SoundItem
{
	M_DECLARE_CLASS(SoundClipItem, SoundItem)

protected:
	bool mIsLoaded;          // 资源是否加载完成
	bool mIsDontDestroy;     // 是否不销毁

public:
	SoundClipItem();
	virtual void onInit() override;
	virtual void onDestroy() override;

	virtual void unload() override;
	virtual void Play() override;
};

MY_END_NAMESPACE