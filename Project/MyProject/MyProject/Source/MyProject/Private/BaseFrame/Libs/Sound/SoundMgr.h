#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
    * @brief 播放音乐和音效
    */
public class SoundMgr : IDispatchObject, ICalleeObject
{
    protected MKeyIndexList<uint, SoundItem> mUniqueId2SoundDic;
    protected TimerItemBase mTimer;
    protected MList<SoundItem> mClearList;
    protected MDictionary<uint, AuxLoaderBase> mId2LoadingItemDic;  // Id 到加载 Item 字典
    protected UniqueNumIdGen mUniqueNumIdGen;
    protected int mMaxPlayerSoundNum;

    public SoundMgr()
    {
        this.mUniqueId2SoundDic = new MKeyIndexList<uint, SoundItem>();
        this.mClearList = new MList<SoundItem>();
        this.mId2LoadingItemDic = new MDictionary<uint, AuxLoaderBase>();
        this.mUniqueNumIdGen = new UniqueNumIdGen(1);
        this.mMaxPlayerSoundNum = 20;
    }

    public void init()
    {
        Ctx.msInstance.mSystemEvent.addSystemEventHandle(SystemEventId.eSEI_FOCUS, this, this.onFocusChangeHandle);
    }

    public void dispose()
    {
        if(null != Ctx.msInstance.mSystemEvent)
        {
            Ctx.msInstance.mSystemEvent.removeSystemEventHandle(SystemEventId.eSEI_FOCUS, this, this.onFocusChangeHandle);
        }

        this.unloadAll();
    }

    public void call(IDispatchObject dispObj, uint uniqueId)
    {

    }

    // 焦点改变事件处理
    public void onFocusChangeHandle(IDispatchObject dispObj, uint uniqueId)
    {
        int index = 0;
        int listLen = this.mUniqueId2SoundDic.count();
        SoundItem soundItem = null;

        // 如果回去焦点
        if (Ctx.msInstance.mSystemEvent.hasFocus())
        {
            while(index < listLen)
            {
                soundItem = this.mUniqueId2SoundDic.get(index);

                if(null != soundItem)
                {
                    soundItem.Play();
                }

                index += 1;
            }
        }
        else
        {
            // 如果失去焦点
            while (index < listLen)
            {
                soundItem = this.mUniqueId2SoundDic.get(index);

                if (null != soundItem)
                {
                    soundItem.Pause();
                }

                index += 1;
            }
        }
    }

    public uint playImpl(SoundParam soundParam)
    {
        uint uniqueId = 0;
        uniqueId = soundParam.mUniqueId;

        if (!soundParam.mIsLoop)
        {
            this.addTimer();
        }

        if (this.mUniqueId2SoundDic.containsKey(uniqueId))      // 如果已经有了直接返回
        {
            if (!this.mUniqueId2SoundDic.value(uniqueId).isInCurState(SoundPlayState.eSS_Play))
            {
                this.mUniqueId2SoundDic.value(uniqueId).Play();
            }
        }
        else
        {
            // 创建
            if (this.isPrefab(soundParam.mPath))
            {
                this.mUniqueId2SoundDic.add(uniqueId, (SoundPrefabItem)SoundPrefabItem.msClassInfo.newObject());
                this.mUniqueId2SoundDic.value(uniqueId).mSoundResType = SoundResType.eSRT_Prefab;

                AuxMusicPrefabLoader auxMusicPrefabLoader = (AuxMusicPrefabLoader)AuxMusicPrefabLoader.msClassInfo.newObject((int)AssetId.eAId_0, DataUtilAsset.convAssetId2Path(AssetId.eAId_0), true);
                auxMusicPrefabLoader.setUniqueInsId(uniqueId);
                auxMusicPrefabLoader.setDestroySelf(true);
                auxMusicPrefabLoader.setIsNeedInsRes(true);
                auxMusicPrefabLoader.setIsInsNeedCoroutine(false);
                this.mId2LoadingItemDic[uniqueId] = auxMusicPrefabLoader;
            }
            else
            {
                this.mUniqueId2SoundDic.add(uniqueId, (SoundClipItem)SoundClipItem.msClassInfo.newObject((int)AssetId.eAId_0, DataUtilAsset.convAssetId2Path(AssetId.eAId_0), true));
                this.mUniqueId2SoundDic.value(uniqueId).mSoundResType = SoundResType.eSRT_Clip;

                AuxMusicLoader auxMusicLoader = (AuxMusicLoader)AuxMusicLoader.msClassInfo.newObject((int)AssetId.eAId_0, DataUtilAsset.convAssetId2Path(AssetId.eAId_0), true);
                auxMusicLoader.setUniqueInsId(uniqueId);
                auxMusicLoader.setDestroySelf(true);
                auxMusicLoader.setIsNeedInsRes(false);
                this.mId2LoadingItemDic[uniqueId] = auxMusicLoader;
            }

            this.mUniqueId2SoundDic.value(uniqueId).setUniqueId(uniqueId);
            this.mUniqueId2SoundDic.value(uniqueId).initParam(soundParam);
            this.mUniqueId2SoundDic.value(uniqueId).Play();     // 设置播放状态

            this.mId2LoadingItemDic[uniqueId].asyncLoad(
                soundParam.mPath,
                null, 
                this.onLoadEventHandle
                );
        }

        return uniqueId;
    }

    private bool isSkipMusic(string path)
    {
        bool ret = true;
        if (path.EndsWith("kill.mp3") || path.EndsWith("beforetime.wav") || path.EndsWith("lasttime.wav"))
        {
            //不限制该音乐不放
            ret = false;
        }
        return ret;
    }

    /** 
        * @brief soundtype:音乐类型，1背景音 2游戏音效
        * @param isUniquePathId 如果是 true，就说明只能包含一个对应音乐的路径
        */
    public uint play(uint uniqueId, string path, float volume, uint soundtype, bool loop_ = true, bool isUniquePathId = false)
    {
        // 如果超过最大数量就不用继续播放了
        if ((this.mUniqueId2SoundDic.count() > this.mMaxPlayerSoundNum) && this.isSkipMusic(path))
        {
            return 0;
        }

        SoundItem soundItem = null;
        uint useUniqueId = uniqueId;

        if (isUniquePathId)
        {
            soundItem = this.getSoundItemByPath(path);
                
            if(null != soundItem)
            {
                useUniqueId = soundItem.getUniqueId();
            }
        }

        if (0 == useUniqueId)
        {
            useUniqueId = this.mUniqueNumIdGen.genNewId();
        }

        //关闭游戏音效
        if ((2 == soundtype) && Ctx.msInstance.mSystemSetting.hasKey("GameMusic"))
        {
            if (Ctx.msInstance.mSystemSetting.getInt("GameMusic") == 0)
            {
                return useUniqueId;
            }
        }
        //关闭背景音乐
        if ((1 == soundtype) && Ctx.msInstance.mSystemSetting.hasKey("MusicModel"))
        {
            if (Ctx.msInstance.mSystemSetting.getInt("MusicModel") == 0)
            {
                return useUniqueId;
            }
        }

        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::play, path = {0}", path), LogTypeId.eLogMusicBug);
        }

        if (this.mUniqueId2SoundDic.containsKey(useUniqueId))
        {
            this.mUniqueId2SoundDic.value(useUniqueId).Play();
        }
        else
        {
            SoundParam param = (SoundParam)SoundParam.msClassInfo.newObject((int)AssetId.eAId_0, DataUtilAsset.convAssetId2Path(AssetId.eAId_0), true);

            param.mPath = path;
            param.mIsLoop = loop_;
            param.volume = volume;
            param.soundtype = soundtype;
            param.mUniqueId = useUniqueId;

            this.playImpl(param);

            param.mLinkClassInfo.deleteObject(param);
        }

        return useUniqueId;
    }

    public void stop(uint unique, string path)
    {
        //this.unload(unique, path);
        this.removeAndDispose(unique, path);
    }

    public void onLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
    {
        AuxLoaderBase loader = dispObj as AuxLoaderBase;

        uint uniqueItemId = 0;
        string origPath = "";

        if (AuxMusicLoaderType.eAMLT_Clip == loader.getMusicLoaderType())
        {
            uniqueItemId = (loader as AuxMusicLoader).getUniqueInsId();
        }
        else if(AuxMusicLoaderType.eAMLT_Prefab == loader.getMusicLoaderType())
        {
            uniqueItemId = (loader as AuxMusicPrefabLoader).getUniqueInsId();
        }

        origPath = loader.getOrigPath();

        if (loader.hasSuccessLoaded())
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::onLoadEventHandle, Success, path = {0}", loader.getOrigPath()), LogTypeId.eLogMusicBug);
            }

            if (this.mUniqueId2SoundDic.containsKey(uniqueItemId))      // 如果有，说明还没被停止
            {
                if (this.mUniqueId2SoundDic.value(uniqueItemId).mSoundResType == SoundResType.eSRT_Prefab)
                {
                    this.mUniqueId2SoundDic.value(uniqueItemId).setResObj((loader as AuxMusicPrefabLoader).getGameObject());
                }
                else
                {
                    this.mUniqueId2SoundDic.value(uniqueItemId).setResObj((loader as AuxMusicLoader).getAudioClip());
                }

                //SoundItem item = this.mUniqueId2SoundDic.value(uniqueItemId);
                //float volume = item.getVolume();
                //uint soundtype = item.soundtype;

                //// 如果当前仍然在播放状态，就继续播放音乐，如果不在，就不用继续播放了
                //if (item.isInCurState(SoundPlayState.eSS_Play))
                //{
                //    // 播放音乐
                //    this.play(uniqueItemId, origPath, volume, soundtype);
                //}
            }
            else
            {
                // 如果运行到这里基本就是出错了
                this.mId2LoadingItemDic.remove(uniqueItemId);
                this.mId2LoadingItemDic[uniqueItemId].mLinkClassInfo.deleteObject(this.mId2LoadingItemDic[uniqueItemId]);
            }
        }
        else if (loader.hasFailed())
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::onLoadEventHandle, Fail, path = {0}", loader.getOrigPath()), LogTypeId.eLogMusicBug);
            }

            //this.deleteSoundItem(this.mUniqueId2SoundDic.value(uniqueItemId));
            this.mUniqueId2SoundDic.value(uniqueItemId).mLinkClassInfo.deleteObject(this.mUniqueId2SoundDic.value(uniqueItemId));

            // 如果加载失败了，直接释放资源
            //this.mId2LoadingItemDic[uniqueItemId].dispose();
            //this.mId2LoadingItemDic.remove(uniqueItemId);
        }

        // 卸载数据，等到不用的时候再卸载，在台式机上没有问题，在手机上会导致 SoundClipItem::mClip 变成 null
        //Ctx.msInstance.mResLoadMgr.unload(uniqueId, this.onLoadEventHandle);
    }

    // 移除一个资源，但是不卸载
    protected void remove(uint uniqueId, string path)
    {
        this.unload(uniqueId, path);
    }

    // 移除并且释放资源一个资源
    protected void removeAndDispose(uint uniqueId, string path)
    {
        SoundItem item = null;
        item = this.getSoundItemByPathOrUniqueId(uniqueId, path);

        //this.unload(uniqueId, path);

        if (null != item)
        {
            item.mLinkClassInfo.deleteObject(item);
        }
    }

    protected void unload(uint uniqueId, string path)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::unload, uniqueId = {0}, path = {1}", uniqueId, path), LogTypeId.eLogMusic);
        }

        if (uniqueId > 0)
        {
            this.unloadByUniqueId(uniqueId);
        }
        else if(!string.IsNullOrEmpty(path))
        {
            this.unloadByOrigPath(path);
        }
    }

    public void unloadByUniqueId(uint uniqueId)
    {
        if (uniqueId > 0)
        {
            if (this.mUniqueId2SoundDic.containsKey(uniqueId))
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::unloadByUniqueId, success, uniqueId = {0}", uniqueId), LogTypeId.eLogMusic);
                }
                //this.mPath2SoundDic[uniqueId].unload();
                this.deleteSoundItem(this.mUniqueId2SoundDic.value(uniqueId));

                AuxLoaderBase loader = null;
                loader = this.mId2LoadingItemDic[uniqueId];
                this.mId2LoadingItemDic.remove(uniqueId);
                loader.mLinkClassInfo.deleteObject(loader);
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::unloadByUniqueId, error, uniqueId = {0},", uniqueId), LogTypeId.eLogMusic);
                }
            }
        }
    }

    public void unloadByOrigPath(string path)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::unloadByOrigPath, start, path = {0}", path), LogTypeId.eLogMusic);
        }

        if (!string.IsNullOrEmpty(path))
        {
            SoundItem item = this.getSoundItemByPath(path);

            if (null != item)
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::unloadByOrigPath, success, path = {0}", path), LogTypeId.eLogMusic);
                }

                this.unloadByUniqueId(item.getUniqueId());
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::unloadByOrigPath, error, path = {0}", path), LogTypeId.eLogMusic);
                }
            }
        }
    }

    public SoundItem getSoundItemByPathOrUniqueId(uint unique, string path)
    {
        SoundItem item = null;

        if(unique > 0)
        {
            item = this.getSoundItemByUniqueId(unique);
        }
        else if(!string.IsNullOrEmpty(path))
        {
            item = this.getSoundItemByPath(path);
        }

        return item;
    }

    public SoundItem getSoundItemByUniqueId(uint unique)
    {
        SoundItem item = null;
        item = this.mUniqueId2SoundDic.value(unique);
        return item;
    }

    public SoundItem getSoundItemByPath(string path)
    {
        SoundItem item = null;

        foreach(System.Collections.Generic.KeyValuePair<uint, SoundItem> kv in this.mUniqueId2SoundDic.getIndexDic().getData())
        {
            if(kv.Value.mPath == path)
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::getSoundItemByPath, success, path = {0}", path), LogTypeId.eLogMusic);
                }

                item = kv.Value;
                break;
            }
        }

        return item;
    }

    // 不要遍历中使用这个函数
    protected void deleteSoundItem(SoundItem item)
    {
        if (MacroDef.ENABLE_LOG)
        {
            Ctx.msInstance.mLogSys.log(string.Format("SoundMgr::delSoundItem, path = {0}", item.mPath), LogTypeId.eLogMusic);
        }

        this.mUniqueId2SoundDic.remove(item.getUniqueId());

        //NumIdBufferObjectFactory.deleteObject(item);
    }

    // 定时释放资源
    public void onTimer(IDispatchObject dispObj, uint uniqueId)
    {
        TimerItemBase time = dispObj as TimerItemBase;
        bool hasNoLoop = false;

        // 遍历看有没有播放完成的
        foreach(SoundItem sound in this.mUniqueId2SoundDic.getList().list())
        {
            if(sound.isEnd())
            {
                this.mClearList.add(sound);
            }
            else if (!sound.mIsLoop)
            {
                hasNoLoop = true;
            }
        }

        foreach(SoundItem sound in this.mClearList.list())
        {
            this.removeAndDispose(sound.getUniqueId(), "");
        }

        this.mClearList.clear();

        if (!hasNoLoop)
        {
            this.mTimer.stopTimer();
        }
    }

    public void addTimer()
    {
        if (this.mTimer == null)
        {
            this.mTimer = new TimerItemBase();
            this.mTimer.mInternal = 0.5f;        // 一分钟遍历一次
            this.mTimer.mIsInfineLoop = true;
            this.mTimer.addTimerHandle(null, this.onTimer, 0);
        }
        else
        {
            // 只有停止的时候才重置数据
            if(this.mTimer.mIsDisposed)
            {
                this.mTimer.reset();
            }
        }

        // 检查是否要加入定时器
        this.mTimer.startTimer();
    }

    protected bool isPrefab(string path)
    {
        bool ret = false;

        if (path.Substring(path.IndexOf(".") + 1) == "prefab")
        {
            ret = true;
        }

        return ret;
    }

    // 卸载所有的资源
    public void unloadAll()
    {
        if (this.mTimer != null)
        {
            this.mTimer.stopTimer();
            this.mTimer = null;
        }

        int index = 0;
        int listLen = this.mUniqueId2SoundDic.getList().count();

        MList<SoundItem> tmpList = new MList<SoundItem>();

        while(index < listLen)
        {
            tmpList.add(this.mUniqueId2SoundDic.get(index));
            index = index + 1;
        }

        // 遍历看有没有播放完成的
        foreach (SoundItem sound in tmpList.list())
        {
            // 卸载声音
            //sound.unload();
            sound.mLinkClassInfo.deleteObject(sound);
        }

        this.mUniqueId2SoundDic.clear();
        this.mClearList.clear();
    }

    // 调整所有的音量
    public void changeAllVolume(float volume)
    {
        int index = 0;
        int listLen = this.mUniqueId2SoundDic.count();
        SoundItem item = null;

        while (index < listLen)
        {
            item = this.mUniqueId2SoundDic.get(index);
            item.setVolume(volume);

            index += 1;
        }
    }
};

MY_END_NAMESPACE