#include "MyProject.h"
#include "SoundClipItem.h"

MY_BEGIN_NAMESPACE(MyNS)

SoundClipItem::SoundClipItem()
{
    
}

void SoundClipItem::onInit()
{
    //base.onInit();

    this->mIsLoaded = false;
    this->mIsDontDestroy = true;
}

void SoundClipItem::onDestroy()
{
    //base.onDestroy();
}

void SoundClipItem::unload()
{
    /*if (MacroDef.ENABLE_LOG)
    {
        Ctx.msInstance.mLogSys.log("SoundClipItem::unload", LogTypeId.eLogMusicBug);
    }

    Ctx.msInstance.mSoundLoadStateCheckMgr.removeSound(this);

    if (this->isInCurState(SoundPlayState.eSS_Play))
    {
        this->Stop();
    }

    base.unload();*/
}

void SoundClipItem::Play()
{
    //if(AudioDataLoadState.Loaded != this->mClip.loadState)
    /*if(!this->mIsLoaded)
    {
        if (MacroDef.ENABLE_LOG)
        {
            if (null != this->mClip)
            {
                Ctx.msInstance.mLogSys.log("SoundClipItem::Play, Clip not null", LogTypeId.eLogMusicBug);
            }
            else
            {
                Ctx.msInstance.mLogSys.log("SoundClipItem::Play, Clip is null", LogTypeId.eLogMusicBug);
            }
        }

        Ctx.msInstance.mSoundLoadStateCheckMgr.addSound(this);
    }

    base.Play();*/
}

MY_END_NAMESPACE