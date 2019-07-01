#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SoundParam : GObject
{
public:
	std::string mPath = "";      // 音乐路径
	bool mIsLoop = true;    // 是否循环播放
	Transform mTrans;       // 播放音乐的对象的位置信息
	float volume;
	uint soundtype;
	uint mUniqueId;

	public SoundParam()
	{
		this.mLinkClassInfo = SoundParam.msClassInfo;
	}

	// 所有都执行完成后调用
	override public void init()
	{
		this.onInit();
	}

	override public void onInit()
	{
		base.onInit();

		this.mPath = "";
		this.mIsLoop = true;
		this.mTrans = null;
		this.volume = 1.0f;
		this.soundtype = 1;
		this.mUniqueId = 0;
	}

	override public void dispose()
	{
		this.onClear();
		this.onDestroy();
	}
};

MY_END_NAMESPACE