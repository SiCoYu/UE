using UnityEngine;

namespace SDK.Lib
{
    public class EffectBase : SceneEntityBase, ICalleeObject
    {
        protected EventDispatch mPlayEndEventDispatch;         // 特效播放完成事件分发
        protected bool mIsAutoRemove;       // 特效播放完成是否自动移除
        protected EffectRenderType mRenderType;     // 特效渲染类型
        protected EffectType mEffectType;       // 特效类型

        protected UnityEngine.Vector3 mPreScale;  // 之前的所放值
        protected bool mIsFirstScale;    // 第一次加载资源没有缩放动画

        public EffectBase()
        {
            this.mIsAutoRemove = false;
            this.mRenderType = EffectRenderType.eShurikenEffectRender;
            this.mEffectType = EffectType.eLinkEffect;
            this.mPlayEndEventDispatch = new AddOnceAndCallOnceEventDispatch();
            this.mPreScale = UtilMath.OneVec3;
            this.mIsFirstScale = true;
        }

        override public void init()
        {
            base.init();

            if(null == this.mRender)
            {
                if (EffectRenderType.eSpriteEffectRender == this.mRenderType)
                {
                    this.mRender = new SpriteEffectRender(this);
                }
                else if (EffectRenderType.eShurikenEffectRender == this.mRenderType)
                {
                    this.mRender = new ShurikenEffectRender(this);
                }
                else if (EffectRenderType.eFxEffectRender == this.mRenderType)
                {
                    this.mRender = new FxEffectRender(this);
                }

                this.getEffectRender().addPlayEndEventHandle(this.onEffectPlayEnd);
            }

            Ctx.msInstance.mSceneEffectMgr.addEffect(this);
        }

        override public void onGetFromPool()
        {
            base.onGetFromPool();
        }

        public void setEffectRenderType(EffectRenderType type_)
        {
            this.mRenderType = type_;
        }

        public void setEffectType(EffectType type_)
        {
            this.mEffectType = type_;
        }

        public EventDispatch getPlayEndEventDispatch()
        {
            return this.mPlayEndEventDispatch;
        }

        public void setPlayEndEventDispatch(EventDispatch value)
        {
            this.mPlayEndEventDispatch = value;
        }

        public bool isAutoRemove()
        {
            return this.mIsAutoRemove;
        }

        public void setIsAutoRemove(bool value)
        {
            this.mIsAutoRemove = value;
        }

        protected EffectRenderBase getEffectRender()
        {
            return this.mRender as EffectRenderBase;
        }

        virtual public void onEffectPlayEnd(IDispatchObject dispObj, uint uniqueId)
        {
            this.mPlayEndEventDispatch.dispatchEvent(this);

            if (this.mIsAutoRemove)
            {
                this.dispose();          // 释放资源
            }
        }

        virtual public void setSelfActor(GameObject go_)
        {
            this.getEffectRender().setSelfActor(go_);
        }

        virtual public void setTableId(int tableId)
        {
            this.getEffectRender().setTableId(tableId);
        }

        virtual public void setLoop(bool bLoop)
        {
            this.getEffectRender().setLoop(bLoop);
        }

        virtual public void play()
        {
            this.getEffectRender().play();
        }

        virtual public void stop()
        {
            this.getEffectRender().stop();
        }

        override public void dispose()
        {
            if (null != Ctx.msInstance.mSceneEffectMgr)
            {
                Ctx.msInstance.mSceneEffectMgr.removeEffect(this);
            }

            base.dispose();
        }

        override public void onTick(float delta, TickMode tickMode)
        {
            this.mRender.onTick(delta, tickMode);
        }

        // 添加特效播放结束处理
        public void addEffectPlayEndHandle(MEventDispatchAction<IDispatchObject> handle)
        {
            this.mPlayEndEventDispatch.addEventHandle(null, handle);
        }

        virtual public void addMoveDestEventHandle(MEventDispatchAction<IDispatchObject> dispObj)
        {

        }

        override public void setPnt(GameObject pntGO_)
        {
            this.getEffectRender().setParentActor(pntGO_);
        }

        public bool isPlay()
        {
            return this.getEffectRender().isPlay();
        }

        public void setKeepLastFrame(bool bKeep)
        {
            this.getEffectRender().setKeepLastFrame(bKeep);
        }

        public void setLoopType(eSpriteLoopType type)
        {
            this.getEffectRender().setLoopType(type);
        }

        // 父节点改变处理
        public void onParentActorChangedHandle(IDispatchObject dispObj, uint uniqueId)
        {
            SceneEntityBase entity = dispObj as SceneEntityBase;

            this.getEffectRender().setParentActor(entity.getEffectSocket());
        }

        public void call(IDispatchObject dispObj, uint uniqueId)
        {

        }

        override public void setScale(UnityEngine.Vector3 value)
        {
            if (!UtilMath.isEqualVec3(this.mScale, value))
            {
                if (this.mIsFirstScale)
                {
                    this.mIsFirstScale = false;
                    this.mPreScale = value;
                }
                else
                {
                    this.mPreScale = this.mScale;
                }

                base.setScale(value);
            }
        }

        override public Vector3 getPreScale()
        {
            return this.mPreScale;
        }

        public void setIsScaleAnim(bool value)
        {
            if(null != this.mRender)
            {
                (this.mRender as EffectRenderBase).setIsScaleAnim(value);
            }
        }

        public bool isScaleAnim()
        {
            bool ret = false;

            if (null != this.mRender)
            {
                ret = (this.mRender as EffectRenderBase).isScaleAnim();
            }

            return ret;
        }
    }
}