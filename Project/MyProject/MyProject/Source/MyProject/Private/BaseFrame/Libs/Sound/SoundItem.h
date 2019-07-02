#pragma once

#include "GObject.h"
#include "SoundResType.h"
#include "SoundPlayState.h"
#include "SoundParam.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief ���ֺ���Ч���������
 */
class SoundItem : public GObject
{
	M_DECLARE_CLASS(SoundItem, GObject)

public:
	FString mPath;           // ��ԴĿ¼
    FString mUniqueStrId;       // ��ԴΨһ Id
    uint mUniqueId;

    SoundResType mSoundResType;

protected:
	SoundPlayState mPlayState;      // ������Ч����״̬

public:
	bool mPlayOnStart;

    ulong mDelay;
    bool mBypassEffects;        // �Ƿ�����Ƶ��Ч
    bool mMute;         // �Ƿ���
    bool mIsLoop;        // �Ƿ�ѭ������
    float mVolume;
    float mPitch;
    bool mScaleOutputVolume;
    uint soundtype;

public:
	SoundItem();
    // ���ж�ִ����ɺ����
	virtual void init() override;
	virtual void onInit() override;
	virtual void onClear();

    // ����
	virtual void destroy() override;
	virtual void onDestroy() override;
    // ����������
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

    // ж��
	virtual void unload();
	bool isEnd();
};

MY_END_NAMESPACE