#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SoundParam : GObject
{
public:
	FString mPath = "";      // 音乐路径
	bool mIsLoop = true;    // 是否循环播放
	float volume;
	uint soundtype;
	uint mUniqueId;

public:
	SoundParam();
	// 所有都执行完成后调用
	virtual void init() override;
	virtual void onInit() override;
	virtual void dispose() override;
};

MY_END_NAMESPACE