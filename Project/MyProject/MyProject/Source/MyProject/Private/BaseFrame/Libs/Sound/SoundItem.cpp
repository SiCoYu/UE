#include "MyProject.h"
#include "SoundItem.h"

MY_BEGIN_NAMESPACE(MyNS)

SoundItem::SoundItem()
{
    
}

// 所有都执行完成后调用
void SoundItem::init()
{
    //base.init();
}

void SoundItem::onInit()
{
    //base.onInit();

    this->mPath = "";
    this->mUniqueStrId = "";
    this->mUniqueId = 0;

    this->mSoundResType = SoundResType::eSRT_Prefab;
    this->mPlayState = SoundPlayState::eSS_None;
    this->mPlayOnStart = true;

    this->mDelay = 0;
    this->mBypassEffects = false;
    this->mMute = false;
    this->mIsLoop = false;
    this->mVolume = 1.0f;
    this->mPitch = 1.0f;
    this->mScaleOutputVolume = true;
    this->soundtype = 0;

    //UtilEngineWrap.setActorName(this->mGo, "SoundGO");
}

void SoundItem::onClear()
{
    //if (null != Ctx.msInstance.mSoundMgr)
    //{
    //    Ctx.msInstance.mSoundMgr.unloadByUniqueId(this->mUniqueId);
    //}

    //this->unload();
    //UtilEngineWrap.setActorName(this->mGo, "SoundGO-HIDE");

    //base.putInPool();
}

// 析构
void SoundItem::destroy()
{
    this->onClear();
    this->onDestroy();
}

void SoundItem::onDestroy()
{
    //base.onDestroy();
}

// 清理并且销毁
void SoundItem::dispose()
{
    this->onClear();
    this->onDestroy();
}

uint SoundItem::getUniqueId()
{
    return this->mUniqueId;
}

void SoundItem::setUniqueId(uint value)
{
    this->mUniqueId = value;
}

void SoundItem::onTick(float delta, TickMode tickMode)
{
    
}

bool SoundItem::isInCurState(SoundPlayState state)
{
    return this->mPlayState == state;
}

void SoundItem::initParam(SoundParam soundParam)
{
    this->mIsLoop = soundParam.mIsLoop;
    this->mPath = soundParam.mPath;
    this->soundtype = soundParam.soundtype;
    this->setVolume(soundParam.volume);
}

void SoundItem::updateParam()
{
    //if (null != this->mAudio)
    {
        this->setVolume(this->mVolume);

        //this->mAudio.minDistance = 1.0f;
        //this->mAudio.maxDistance = 50;

        if(this->mPlayState == SoundPlayState::eSS_Play)
        {
            this->Play();
        }
    }
}

float SoundItem::getVolume()
{
    return this->mVolume; 
}

void SoundItem::setVolume(float value)
{
/*    if (null != this->mAudio)
    {
        if (this->mScaleOutputVolume)
        {
            this->mAudio.volume = ScaleVolume(value);
        }
        else
        {
            this->mAudio.volume = value;
        }
    }   */         

    this->mVolume = value;
}

float SoundItem::getPitch()
{
    return this->mPitch; 
}

void SoundItem::setPitch(float value)
{
    this->mPitch = value;

    //if(null != this->mAudio)
    //{
    //    this->mAudio.pitch = value;
    //}
}

void SoundItem::Start()
{
    if (this->mPlayOnStart)
    {
        this->Play();
    }
}

void SoundItem::Pause()
{
    this->mPlayState = SoundPlayState::eSS_Pause;

    //if (null != this->mAudio)
    //{
    //    this->mAudio.Pause();
    //}
}

void SoundItem::Play()
{
    this->mPlayState = SoundPlayState::eSS_Play;

    /*if (null != this->mAudio)
    {
        if (SoundPlayState.eSS_Pause == this->mPlayState)
        {
            this->mAudio.UnPause();
        }
        else
        {
            this->mAudio.Play(this->mDelay);
        }
    }*/
}

void SoundItem::Stop()
{
    this->mPlayState = SoundPlayState::eSS_Stop;

    //if (null != this->mAudio)
    //{
    //    this->mAudio.Stop();
    //}
}

void SoundItem::SetPitch(float p)
{
    this->setPitch(p);
}

float SoundItem::ScaleVolume(float v)
{
    //v = Mathf.Pow(v, 4);
    //return Mathf.Clamp(v, 0f, 1f);
	return 0;
}

// 卸载
void SoundItem::unload()
{
            
}

bool SoundItem::isEnd()
{
    bool ret = false;

    if (SoundPlayState::eSS_Play == mPlayState)     // 如果处于播放状态的
    {
        //if (null != this->mAudio)
        //{
        //    ret = !this->mAudio.isPlaying;
        //}
    }

    return ret;
}

MY_END_NAMESPACE