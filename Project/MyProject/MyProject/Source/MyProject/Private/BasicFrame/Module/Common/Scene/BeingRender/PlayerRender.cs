using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief Player 渲染器
     */
    public class PlayerRender : BeingEntityRender
    {
        private float angle = 0;
        private float delta_angle = 0;
        public bool isBig = false;
        public float scale = 0.01f;
        protected GameObject mArrowDirection;
        protected bool mIsArrowDirectionScaleDirty;

        /**
         * @brief 构造函数
         */
        public PlayerRender(SceneEntityBase entity_)
            : base(entity_)
        {
            /*int _angle = UtilMath.RangeRandom(1, 10);
            this.delta_angle = 0.1f * _angle;

            int flat = UtilMath.RangeRandom(1, 100);
            this.delta_angle = flat > 50 ? this.delta_angle : -this.delta_angle;*/
            this.delta_angle = 90f;

            this.mIsArrowDirectionScaleDirty = false;
        }

        override protected void _onSelfChanged()
        {
            base._onSelfChanged();

            if (!MacroDef.MOBILE_PLATFORM)
            {
                this.setSelfName((this.mEntity as BeingEntity).getName() + " + " + mEntity.getThisId());
            }

            //if(EntityType.ePlayerMain == this.mEntity.getEntityType() ||
            //   EntityType.ePlayerOther == this.mEntity.getEntityType())
            //{
            //    this.mArrowDirection = UtilEngineWrap.TransFindChildByPObjAndPath(this.mSelfActor, "ArrowDirection");
            //    this.updateArrowDirectionScale();
            //}
        }

        /**
         * @brief 释放基本数据
         */
        override public void dispose()
        {
            this.isBig = false;
            this.scale = 0.01f;
            base.dispose();
        }

        override public void attachToParentNode(EntityRenderBase render)
        {
            if(EntityType.ePlayerMain == this.mEntity.getEntityType() ||
               EntityType.ePlayerOther == this.mEntity.getEntityType())
            {
                if(this.isSelfValid() && render.isSelfValid())
                {
                    UtilEngineWrap.SetParent(render.getSelfActor(), this.mSelfActor, false);

                    if (EntityType.ePlayerMain == this.mEntity.getEntityType())
                    {
                        UtilEngineWrap.setSpringJointBody(render.getSelfActor(), this.mSelfActor);
                    }
                }
            }
        }

        private void onChangeTrailRender()
        {
            if(this.mEntity.getEntityType() != EntityType.ePlayerMain && 
               this.mEntity.getEntityType() != EntityType.ePlayerOther)
            {
                return;
            }
        }

        private void onRotateBeGod()
        {
            //无敌光环旋转
			if (null != this.mEntityRenderCom && null != this.mEntityRenderCom.mBeGodGo && (this.mEntity as PlayerChild).mParentPlayer.getIsGod())
            {
                angle += this.delta_angle;
                angle %= 360f;

                UnityEngine.Quaternion rotation = UnityEngine.Quaternion.Euler(new UnityEngine.Vector3(0, 0, angle));

                this.mEntityRenderCom.mBeGodGo.transform.localRotation = rotation;
            }
        }

        override public void onTick(float delta, TickMode tickMode)
        {
            base.onTick(delta, tickMode);
            this.onChangeTrailRender();
            this.onRotateBeGod();

            if (null == this.mEntityRenderCom || null == this.mEntityRenderCom.mOutlineSpriteRender)
            {
                return;
            }

            this.mEntityRenderCom.mOutlineSpriteRender.transform.localScale = new UnityEngine.Vector2(this.scale, this.scale);
            if (!this.isBig)
            {
                this.scale += 0.01f;
            }
            else
            {
                //this.scale -= 0.01f;
            }
            if(this.scale > 0.4f)
            {
                this.isBig = true;
                this.scale = 0;
            }
            if (this.scale < 0.01f)
            {
                this.isBig = false;
            }
        }

        override public void updateArrowDirectionScale()
        {
            if(this.mEntity.getEntityType() == EntityType.ePlayerMain &&
               this.mEntity.getEntityType() == EntityType.ePlayerOther)
            {
                if (null != this.mArrowDirection)
                {
                    if (this.mIsArrowDirectionScaleDirty)
                    {
                        this.mIsArrowDirectionScaleDirty = false;
                        UtilEngineWrap.setPos(this.mArrowDirection.transform, this.mEntity.getArrowDirectionScale());
                    }
                }
                else
                {
                    this.mIsArrowDirectionScaleDirty = true;
                }
            }
        }
    }
}