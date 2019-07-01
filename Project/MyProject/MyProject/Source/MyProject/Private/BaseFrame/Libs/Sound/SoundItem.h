#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
    * @brief ���ֺ���Ч���������
    */
public class SoundItem : GObject, ITickedObject, INoOrPriorityObject
{
    public string mPath;           // ��ԴĿ¼
    public string mUniqueStrId;       // ��ԴΨһ Id
    public uint mUniqueId;

    public SoundResType mSoundResType;
    protected SoundPlayState mPlayState;      // ������Ч����״̬
    public Transform mTrans;       // λ����Ϣ
    public GameObject mGo;         // audio ��� GameObject ����
    public AudioSource mAudio;             // ��Դ
    public bool mPlayOnStart;

    public ulong mDelay;
    public bool mBypassEffects;        // �Ƿ�����Ƶ��Ч
    public bool mMute;         // �Ƿ���
    public bool mIsLoop;        // �Ƿ�ѭ������
    public float mVolume;
    public float mPitch;
    public bool mScaleOutputVolume;
    public uint soundtype;

    public SoundItem()
    {
        this.mGo = null;
        this.mAudio = null;
        this.mTrans = null;
    }

    // ���ж�ִ����ɺ����
    override public void init()
    {
        base.init();
    }

    override public void onInit()
    {
        base.onInit();

        this.mPath = "";
        this.mUniqueStrId = "";
        this.mUniqueId = 0;

        this.mSoundResType = SoundResType.eSRT_Prefab;
        this.mPlayState = SoundPlayState.eSS_None;
        this.mPlayOnStart = true;

        this.mDelay = 0;
        this.mBypassEffects = false;
        this.mMute = false;
        this.mIsLoop = false;
        this.mVolume = 1.0f;
        this.mPitch = 1.0f;
        this.mScaleOutputVolume = true;
        this.soundtype = 0;

        UtilEngineWrap.setActorName(this.mGo, "SoundGO");
    }

    override public void onClear()
    {
        if (null != Ctx.msInstance.mSoundMgr)
        {
            Ctx.msInstance.mSoundMgr.unloadByUniqueId(this.mUniqueId);
        }

        this.unload();
        UtilEngineWrap.setActorName(this.mGo, "SoundGO-HIDE");

        base.putInPool();
    }

    // ����
    override public void destroy()
    {
        this.onClear();
        this.onDestroy();
    }

    override public void onDestroy()
    {
        this.mAudio = null;

        base.onDestroy();
    }

    // ����������
    override public void dispose()
    {
        this.onClear();
        this.onDestroy();
    }

    public uint getUniqueId()
    {
        return this.mUniqueId;
    }

    public void setUniqueId(uint value)
    {
        this.mUniqueId = value;
    }

    public void onTick(float delta, TickMode tickMode)
    {
        this.checkLoadState();
    }

    virtual protected void checkLoadState()
    {

    }

    public bool isInCurState(SoundPlayState state)
    {
        return this.mPlayState == state;
    }

    public virtual void setResObj(UnityEngine.Object go_)
    {

    }

    public void initParam(SoundParam soundParam)
    {
        this.mTrans = soundParam.mTrans;
        this.mIsLoop = soundParam.mIsLoop;
        this.mPath = soundParam.mPath;
        this.soundtype = soundParam.soundtype;
        this.setVolume(soundParam.volume);
    }

    protected void updateParam()
    {
        if (this.mTrans != null)
        {
            this.mGo.transform.position = mTrans.position;
        }

        if (null != this.mAudio)
        {
            //this.mAudio = this.mGo.GetComponent<AudioSource>();
            //this.mAudio.rolloffMode = AudioRolloffMode.Logarithmic;
            this.mAudio.loop = this.mIsLoop;
            //this.mAudio.dopplerLevel = 0f;
            //this.mAudio.spatialBlend = 0f;
            this.setVolume(this.mVolume);

            //this.mAudio.minDistance = 1.0f;
            //this.mAudio.maxDistance = 50;

            if(this.mPlayState == SoundPlayState.eSS_Play)
            {
                this.Play();
            }
        }
    }

    public float getVolume()
    {
        return this.mVolume; 
    }

    public void setVolume(float value)
    {
        if (null != this.mAudio)
        {
            if (this.mScaleOutputVolume)
            {
                this.mAudio.volume = ScaleVolume(value);
            }
            else
            {
                this.mAudio.volume = value;
            }
        }            

        this.mVolume = value;
    }

    public float getPitch()
    {
        return this.mPitch; 
    }

    public void setPitch(float value)
    {
        this.mPitch = value;

        if(null != this.mAudio)
        {
            this.mAudio.pitch = value;
        }
    }

    public void Start()
    {
        if (this.mPlayOnStart)
        {
            this.Play();
        }
    }

    public void Pause()
    {
        this.mPlayState = SoundPlayState.eSS_Pause;

        if (null != this.mAudio)
        {
            this.mAudio.Pause();
        }
    }

    virtual public void Play()
    {
        this.mPlayState = SoundPlayState.eSS_Play;

        if (null != this.mAudio)
        {
            if (SoundPlayState.eSS_Pause == this.mPlayState)
            {
                this.mAudio.UnPause();
            }
            else
            {
                this.mAudio.Play(this.mDelay);
            }
        }
    }

    public void Stop()
    {
        this.mPlayState = SoundPlayState.eSS_Stop;

        if (null != this.mAudio)
        {
            this.mAudio.Stop();
        }
    }

    public void SetPitch(float p)
    {
        this.setPitch(p);
    }

    // TODO: we should consider using this dB scale as an option when porting these changes
    // over to unity-bowerbird: http://wiki.unity3d.com/index.php?title=Loudness
    /*
    * Quadratic scaling of actual volume used by AudioSource. Approximates the proper exponential.
    */
    public float ScaleVolume(float v)
    {
        v = Mathf.Pow(v, 4);
        return Mathf.Clamp(v, 0f, 1f);
    }

    // ж��
    public virtual void unload()
    {
            
    }

    public bool isEnd()
    {
        bool ret = false;

        if (SoundPlayState.eSS_Play == mPlayState)     // ������ڲ���״̬��
        {
            if (null != this.mAudio)
            {
                ret = !this.mAudio.isPlaying;
            }
        }

        return ret;
    }
};

MY_END_NAMESPACE