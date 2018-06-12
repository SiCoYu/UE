using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 特效渲染器比较特殊， Render 中的包含真正的 Render ，其他的模型都是 Render 直接包含显示对象
     */
    public class EffectSpriteRender : EntityRenderBase
    {
        protected SpriteRenderSpriteAni mSpriteAniRender;

        public EffectSpriteRender(SceneEntityBase entity_) :
            base(entity_)
        {
            this.mSpriteAniRender = new SpriteRenderSpriteAni(mEntity);
        }

        public SpriteRenderSpriteAni getSpriteAniRender()
        {
            return this.mSpriteAniRender;
        }

        public void setSpriteAniRender(SpriteRenderSpriteAni value)
        {
            this.mSpriteAniRender = value;
        }

        override public void dispose()
        {
            if (this.mSpriteAniRender != null)
            {
                this.mSpriteAniRender.dispose();
                this.mSpriteAniRender = null;
            }
        }

        override public void setClientDispose(bool isDispose)
        {
            base.setClientDispose(isDispose);
            this.mSpriteAniRender.setClientDispose(isDispose);
        }

        override public GameObject getSelfActor()
        {
            return this.mSpriteAniRender.getSelfActor();
        }

        override public Transform transform()
        {
            return this.mSpriteAniRender.getSelfActor().transform;
        }

        override public void onTick(float delta, TickMode tickMode)
        {
            this.mSpriteAniRender.onTick(delta, tickMode);
        }

        override public void setSelfActor(GameObject rhv)
        {
            this.mSpriteAniRender.setSelfActor(rhv);
        }

        override public void setParentActor(GameObject pntGO_)
        {
            this.mSpriteAniRender.setParentActor(pntGO_);
        }

        override public bool checkRender()
        {
            return this.mSpriteAniRender.checkRender();
        }

        public bool isPlay()
        {
            return this.mSpriteAniRender.isPlay();
        }
    }
}