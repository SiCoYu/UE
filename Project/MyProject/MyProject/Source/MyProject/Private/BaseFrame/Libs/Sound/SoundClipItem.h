#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
    * @brief 直接加载声音文件
    */
public class SoundClipItem : SoundItem
{
    new public static MClassInfo msClassInfo;

    public AudioClip mClip;            // 声音资源放在 prefab 中国
    protected bool mIsLoaded;          // 资源是否加载完成
    protected bool mIsDontDestroy;     // 是否不销毁

    public SoundClipItem()
    {
        this.mLinkClassInfo = SoundClipItem.msClassInfo;
    }

    override public void onInit()
    {
        base.onInit();

        this.mIsLoaded = false;
        this.mIsDontDestroy = true;
    }

    override public void onDestroy()
    {
        if (this.mGo != null)
        {
            //mClip.UnloadAudioData();
            UtilEngineWrap.Destroy(this.mGo);
            //UtilEngineWrap.UnloadUnusedAssets();
            this.mGo = null;
        }

        this.mClip = null;

        base.onDestroy();
    }

    public override void setResObj(UnityEngine.Object go_)
    {
        if (MacroDef.ENABLE_LOG)
        {
            if (go_)
            {
                Ctx.msInstance.mLogSys.log("SoundClipItem::setResObj, go_ no null", LogTypeId.eLogMusicBug);
            }
            else
            {
                Ctx.msInstance.mLogSys.log("SoundClipItem::setResObj, go_ is null", LogTypeId.eLogMusicBug);
            }
        }

        this.mClip = go_ as AudioClip;

        if (null == this.mGo)
        {
            this.mGo = UtilEngineWrap.createGameObject("SoundGO");
        }

        if(this.mIsDontDestroy)
        {
            UtilEngineWrap.DontDestroyOnLoad(this.mGo);
        }

        if (this.mClip == null)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("SoundClipItem::setResObj, Clip is null", LogTypeId.eLogMusicBug);
            }

            return;
        }

        this.mAudio = UtilEngineWrap.AddComponent<AudioSource>(this.mGo);
        this.mAudio.clip = mClip;

        this.updateParam();
    }

    public override void unload()
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log("SoundClipItem::unload", LogTypeId.eLogMusicBug);
        }

        Ctx.msInstance.mSoundLoadStateCheckMgr.removeSound(this);

        if (this.isInCurState(SoundPlayState.eSS_Play))
        {
            this.Stop();
        }

        base.unload();
    }

    override public void Play()
    {
        //if(AudioDataLoadState.Loaded != this.mClip.loadState)
        if(!this.mIsLoaded)
        {
            if (MacroDef.ENABLE_LOG)
            {
                if (null != this.mClip)
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

        base.Play();
    }

    // 检查加载状态
    override protected void checkLoadState()
    {
        if (null != this.mClip && AudioDataLoadState.Loaded == this.mClip.loadState)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("SoundClipItem::checkLoadState, set", LogTypeId.eLogMusicBug);
            }

            this.mIsLoaded = true;
            this.Play();
            Ctx.msInstance.mSoundLoadStateCheckMgr.removeSound(this);
        }
        else
        {
            if (MacroDef.ENABLE_LOG)
            {
                if (null == this.mClip)
                {
                    Ctx.msInstance.mLogSys.log("SoundClipItem::checkLoadState, Clip is null", LogTypeId.eLogMusicBug);

                    GameObject go = UtilEngineWrap.findChildActorFromRootByName("SoundGO");

                    if(null == go)
                    {
                        Ctx.msInstance.mLogSys.log("SoundClipItem::checkLoadState, GameObject is destroy", LogTypeId.eLogMusicBug);
                    }
                }
            }

            Ctx.msInstance.mSoundLoadStateCheckMgr.removeSound(this);
        }
    }
}

MY_END_NAMESPACE