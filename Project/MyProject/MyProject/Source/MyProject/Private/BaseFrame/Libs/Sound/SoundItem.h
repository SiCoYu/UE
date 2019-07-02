#pragma once

#include "GObject.h"
#include "SoundResType.h"
#include "SoundPlayState.h"
#include "SoundParam.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 音乐和音效都是这个类
 */
class SoundItem : public GObject
{
	M_DECLARE_CLASS(SoundItem, GObject)

public:
	FString mPath;           // 资源目录
    FString mUniqueStrId;       // 资源唯一 Id
    uint mUniqueId;

    SoundResType mSoundResType;

protected:
	SoundPlayState mPlayState;      // 音乐音效播放状态

public:
	bool mPlayOnStart;

    ulong mDelay;
    bool mBypassEffects;        // 是否开启音频特效
    bool mMute;         // 是否静音
    bool mIsLoop;        // 是否循环播放
    float mVolume;
    float mPitch;
    bool mScaleOutputVolume;
    uint soundtype;

public:
	SoundItem();
    // 所有都执行完成后调用
	virtual void init() override;
	virtual void onInit() override;
	virtual void onClear();

    // 析构
	virtual void destroy() override;
	virtual void onDestroy() override;
    // 清理并且销毁
	virtual void dispose() override;
	uint getUniqueId();
	void setUniqueId(uint value);
	void onTick(float delta, TickMode tickMode);

public:
	bool isInCurState(SoundPlayState state);
	void initParam(SoundParam soundParam);

protected:
	void updateParam();

public:
	float getVolume();
	void setVolume(float value);

	float getPitch();
	void setPitch(float value);
	void Start();
	void Pause();

	virtual void Play();

	void Stop();

	void SetPitch(float p);
	float ScaleVolume(float v);

    // 卸载
	virtual void unload();
	bool isEnd();
};

MY_END_NAMESPACE