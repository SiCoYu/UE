using UnityEngine;

namespace SDK.Lib
{
	/**
	 * @brief 场景中的玩家
	 */
	public class Player : BeingEntity
	{
        public UniqueNumIdGen mUniqueNumIdGen;      // 子弹唯一 Id 生成
        public UniqueNumIdGen mBulletIDGentor;

        // 位置改变量，主要是暂时移动 child，以后改通知为服务器 child 位置，就不用这样修改了
        protected UnityEngine.Vector3 mDeltaPos;

        public uint mPlaneIndex = 0;//皮肤ID
        public uint mBulletIndex = 0; //子弹ID
        public uint mFormationIndex = 1;//阵形id
        private uint mIsFastSpeed = 0;//0:正常速度 1:分裂速度
        private bool mIsSpeedStateChanged = false;
        protected EffectBase mNumEffect;    // 显示的数量特效
        public int mRank = 0;
        private int old_Rank = -1;

        protected Vector3 mArrowDirectionScale;       // 箭头缩放
        private System.Text.StringBuilder stringBuilder = new System.Text.StringBuilder();

        public Player()
		{
            //mSkinAniModel.m_modelList = new SkinSubModel[(int)ePlayerModelType.eModelTotal];
            //int idx = 0;
            //while (idx < (int)ePlayerModelType.eModelTotal)
            //{
            //    mSkinAniModel.m_modelList[idx] = new SkinSubModel();
            //    ++idx;
            //}

            this.mUniqueNumIdGen = new UniqueNumIdGen(0);
            this.mBulletIDGentor = new UniqueNumIdGen(0);
        }

        override protected void _onPreInit()
        {
            base._onPreInit();

            if(null != this.mAnimFSM)
            {
                this.mAnimFSM.init();
            }
            if(null != this.mAnimatorControl)
            {
                this.mAnimatorControl.init();
            }
        }

        protected override void _onPostInit()
        {
            base._onPostInit();

            if (this.getEntityType() == EntityType.ePlayerMain ||
                this.getEntityType() == EntityType.ePlayerOther)
            {
                if (null == this.mHud)
                {
                    this.mHud = Ctx.msInstance.mHudSystem.createHud(this);
                }

                this.mHud.init();

                if (this.mIsClipVisible)
                {
                    this.mHud.onClipShow();
                }
                else
                {
                    this.mHud.onClipHide();
                }
            }
        }

        override public void onDestroy()
        {
            if (null != this.mNumEffect)
            {
                this.mNumEffect.dispose();
                this.mNumEffect = null;
            }

            base.onDestroy();
        }

        override public void onPutInPool()
        {
            this.mPlaneIndex = 0;
            this.mBulletIndex = 0;
            this.mFormationIndex = 1;
            this.mIsFastSpeed = 0;//0:正常速度 1:分裂速度
            this.mIsSpeedStateChanged = false;
            this.mRank = 0;
            this.old_Rank = -1;

            if(null != this.mNumEffect)
            {
                EntityNumIdBufferObjectFactory.deleteObject(this.mNumEffect);
                this.mNumEffect = null;
            }

            base.onPutInPool();
        }

        override public void autoHandle()
        {
            base.autoHandle();
        }

        override public void initRender()
        {
            this.mRender = new PlayerRender(this);
            this.mRender.init();
        }

        protected override void _onPreTick(float delta, TickMode tickMode)
        {
            base._onPreTick(delta, tickMode);
        }

        protected override void _onPostTick(float delta, TickMode tickMode)
        {
            base._onPostTick(delta, tickMode);

            if (null != this.mAnimFSM)
            {
                this.mAnimFSM.UpdateFSM();
            }
        }

        public override void show()
        {
            base.show();

            if (null != this.mNumEffect)
            {
                this.mNumEffect.show();
            }
        }

        public override void hide()
        {
            base.hide();

            if (null != this.mNumEffect)
            {
                this.mNumEffect.hide();
            }
        }

        override public void setPos(UnityEngine.Vector3 pos)
        {
            UnityEngine.Vector3 origPos = this.mPos;
            base.setPos(pos);
            this.mDeltaPos = this.mPos - origPos;
        }

        override public void setDestPos(UnityEngine.Vector3 pos, bool immePos)
        {
            base.setDestPos(pos, immePos);
        }

        public UnityEngine.Vector3 getDeltaPos()
        {
            return this.mDeltaPos;
        }

        // 获取所有的 ChildMovement
        public PlayerMovement[] getAllChildMovement()
        {
            return null;
        }

        public MList<SceneEntityBase> getChildList()
        {
            return null;
        }

        public bool isExistThisId(uint thisId)
        {
            return false;
        }

        public bool getIsDead()
        {
            return false;
        }

        override public void attachToParentNode(EntityRenderBase render)
        {
            base.attachToParentNode(render);

            if (EntityType.ePlayerMain == this.mEntityType ||
                EntityType.ePlayerOther == this.mEntityType)
            {
                this.mRender.attachToParentNode(render);
            }
        }

        // 进入可见
        override public void onClipShow()
        {
            base.onClipShow();
            
            if (null != this.mNumEffect)
            {
                this.mNumEffect.onClipShow();
            }

            //标识
            if(null != this.mHud)
            {
                this.mHud.setScore(stringBuilder.ToString());
                if (this.mRank <= 0 || this.mRank > 3)
                {
                    this.mHud.getRank().hide();
                }
                else
                {
                    this.mHud.getRank().show();
                }
            }
        }

        // 离开可见
        override public void onClipHide()
        {
            base.onClipHide();

            if(null != this.mNumEffect)
            {
                this.mNumEffect.onClipHide();
            }

            if(null != this.mHud)
            {
                if (this.mRank >= 1 && this.mRank <= 3)
                {
                    this.mHud.getRank().hide();
                }
            }
        }

        public void setScore(uint score)
        {
            stringBuilder.Remove(0, stringBuilder.Length);
            if (score >= 0 && score < 1500)
            {
                stringBuilder.Append("<color=#FCFCFCFF>");
                stringBuilder.Append(score);
                stringBuilder.Append("</color>");
            }
            else if (score >= 1500 && score < 3000)
            {
                stringBuilder.Append("<color=#5CACEEFF>");
                stringBuilder.Append(score);
                stringBuilder.Append("</color>");
            }
            else if (score >= 3000 && score < 15000)
            {
                stringBuilder.Append("<color=#EEEE00FF>");
                stringBuilder.Append(score);
                stringBuilder.Append("</color>");
            }
            else if (score >= 15000 && score < 30000)
            {
                stringBuilder.Append("<color=#7CFC00FF>");
                stringBuilder.Append(score);
                stringBuilder.Append("</color>");
            }
            else if (score >= 30000 && score < 75000)
            {
                stringBuilder.Append("<color=#A020F0FF>");
                stringBuilder.Append(score);
                stringBuilder.Append("</color>");
            }
            else
            {
                stringBuilder.Append("<color=#EE0000FF>");
                stringBuilder.Append(score);
                stringBuilder.Append("</color>");
            }

            this.mHud.setScore(stringBuilder.ToString());
        }

        public void setRank(int rank)
        {
        }

        public void setIsFastSpeed(uint state)
        {
            this.mIsFastSpeed = state;
            this.mIsSpeedStateChanged = false;
        }

        public uint getIsFastSpeed()
        {
            return this.mIsFastSpeed;
        }

        public bool getIsSpeedStateChanged()
        {
            return this.mIsSpeedStateChanged;
        }

        public void setIsSpeedStateChanged(bool value)
        {
            this.mIsSpeedStateChanged = value;
        }

        public void addNumEffect(float scaleFactor)
        {
            if (null == this.mNumEffect)
            {
                this.mNumEffect = Ctx.msInstance.mSceneEffectMgr.addLinkEffect(1, this.getEffectSocket());
                (this.mNumEffect as LinkEffect).setLinkedEntity(this);
                this.addSelfActorChangedHandle(this.mNumEffect, this.mNumEffect.onParentActorChangedHandle);
                this.mNumEffect.setSortingOrder(this.getSortingOrder());
                this.mNumEffect.setIsScaleAnim(true);
            }

            if(this.mIsClipVisible)
            {
                this.mNumEffect.onClipShow();
            }

            Vector3 scaleVector = this.mNumEffect.getScale();
            scaleVector.x = scaleFactor;
            scaleVector.y = scaleFactor;
            scaleVector.z = scaleFactor;
            this.mNumEffect.setScale(scaleVector);

            this.mNumEffect.setRotate(this.getRotate());
        }

        public void removeNumEffect()
        {
            if(null != this.mNumEffect)
            {
                EntityNumIdBufferObjectFactory.deleteObject(this.mNumEffect);
                this.mNumEffect = null;
            }
        }

        override public void setRotate(Quaternion rotation)
        {
            base.setRotate(rotation);

            if (null != this.mNumEffect)
            {
                this.mNumEffect.setRotate(rotation);
            }
        }

        override public int getSortingOrder()
        {
            return 0;
        }

        public EffectBase getNumEffect()
        {
            return this.mNumEffect;
        }

        public void setArrowDirectionScale(float scale)
        {
            this.mArrowDirectionScale.x = scale;
            this.mArrowDirectionScale.y = scale;
            this.mArrowDirectionScale.z = scale;

            if(null != this.mRender)
            {
                this.mRender.updateArrowDirectionScale();
            }
        }

        override public Vector3 getArrowDirectionScale()
        {
            return this.mArrowDirectionScale;
        }
    }
}