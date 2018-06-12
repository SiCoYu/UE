using UnityEngine;

namespace SDK.Lib
{
    public class EffectRenderBase : EntityRenderBase
    {
        protected bool mIsScaleAnim;        // 缩放是否使用动画

        public EffectRenderBase(SceneEntityBase entity_) :
            base(entity_)
        {
            this.mIsScaleAnim = false;
        }

        virtual public void addPlayEndEventHandle(MEventDispatchAction<IDispatchObject> handle)
        {

        }

        virtual public void setSelfActor(GameObject go_)
        {
            
        }

        virtual public void setTableId(int tableId)
        {
            
        }

        virtual public void setLoop(bool bLoop)
        {
            
        }

        virtual public void play()
        {
            
        }

        virtual public void stop()
        {
            
        }

        override public void onTick(float delta, TickMode tickMode)
        {
            
        }

        override public void setParentActor(GameObject pntGO_)
        {
            base.setParentActor(pntGO_);
        }

        virtual public bool isPlay()
        {
            return false;
        }

        virtual public void setKeepLastFrame(bool bKeep)
        {

        }

        virtual public void setLoopType(eSpriteLoopType type)
        {

        }

        public void setIsScaleAnim(bool value)
        {
            this.mIsScaleAnim = value;
        }

        public bool isScaleAnim()
        {
            return this.mIsScaleAnim;
        }
    }
}