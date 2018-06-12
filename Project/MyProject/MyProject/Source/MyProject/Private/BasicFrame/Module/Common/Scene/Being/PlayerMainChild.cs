namespace SDK.Lib
{
    public class PlayerMainChild : PlayerChild
    {
        public PlayerMainChild()
        {
            this.mTypeId = "PlayerMainChild";
            this.mEntityType = EntityType.ePlayerMainChild;
            this.mMovement = new PlayerMainChildMovement(this);
            this.mAttack = new PlayerMainChildAttack(this);
            this.mEntityUniqueId = Ctx.msInstance.mPlayerMgr.genChildNewStrId();

            this.setLastMergedTime();

            //this.mPlayerMainChildAI = new PlayerMainChildAI(this);
            //(this.mParentPlayer as PlayerMain).addVehicle(this.mPlayerMainChildAI.getVehicle());
            //this.mPlayerMainChildAI.setVehicleList((this.mParentPlayer as PlayerMain).getNeighbors());
        }

        override public void initRender()
        {
            if (!this.isPrefabPathValid())
            {
                this.setPrefabPath("World/Model/PlayerMain.prefab");
            }

            if (null == this.mRender)
            {
                this.mRender = new PlayerMainChildRender(this);
            }

            this.mRender.init();
        }

        protected override void _onPreInit()
        {
            base._onPreInit();

            this.mMovement.init();
            this.mAttack.init();
            //this.mPlayerMainChildAI.init();
        }

        public override void onTick(float delta, TickMode tickMode)
        {
            base.onTick(delta, tickMode);

            //this.mPlayerMainChildAI.onTick(delta, tickMode);
        }

        public void postUpdate()
        {
            if(this.mRender.isValid())
            {
                this.setRenderPos(this.mRender.getPos());
            }
        }

        public override void onDestroy()
        {
            //(this.mParentPlayer as PlayerMain).removeVehicle(this.mPlayerMainChildAI.getVehicle());

            base.onDestroy();

            if (null != Ctx.msInstance.mGlobalDelegate)
            {
                Ctx.msInstance.mGlobalDelegate.mMainChildMassChangedDispatch.dispatchEvent(null);
            }
        }

        override public void onPutInPool()
        {
            base.onPutInPool();

            Ctx.msInstance.mGlobalDelegate.mMainChildMassChangedDispatch.dispatchEvent(null);
        }

        public override void dispose()
        {
            base.dispose();
        }

        public override void putInPool()
        {
            base.putInPool();
        }

        override public void setBeingState(BeingState state)
        {
            base.setBeingState(state);

            if(BeingState.eBSBirth == this.mBeingState)
            {
                this.mMoveSpeedFactor = 5;
            }
            else
            {
                this.mMoveSpeedFactor = 1;
            }
        }

        // 自己当前是否在分裂目标点的后面
        public bool isBehindTargetPoint()
        {
            return false;
        }

        // 是否可以执行合并操作，能否合并只有一个冷却时间条件
        override public bool canMerge()
        {
            bool ret = false;

            return ret;
        }

        override public void addParentOrientChangedhandle()
        {
            (this.mMovement as PlayerMainChildMovement).addParentOrientChangedhandle();
        }

        // 接触跟随，但是不能融合
        override public void contactWithAndFollowButNotMerge(BeingEntity bBeing)
        {
            PlayerMainChild otherChild = bBeing as PlayerMainChild;
            if(null != otherChild)
            {
                UnityEngine.Quaternion quad = otherChild.getDestRotate();
                this.setNotMergeRotate(quad);
            }
        }

        // 移动到中心点
        override public void moveToCenter()
        {
            
        }

        override public void setDestPos(UnityEngine.Vector3 pos, bool immePos)
        {
            base.setDestPos(pos, immePos);
        }

        override public void setRenderPos(UnityEngine.Vector3 pos)
        {
            if (!UtilEngineWrap.isInFakePos(pos) && !UtilMath.isEqualVec3(this.mPos, pos))
            {
                this.mPos = pos;

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("BeingEntity::setRenderPos, BasicInfo is {0}, mPosX = {1}, mPosY = {2}, mPosZ = {3}", this.getBasicInfoStr(), this.mPos.x, this.mPos.y, this.mPos.z), LogTypeId.eLogBeingMove);
                }
            }
        }

        override public void updateState(Vehicle2D vehicle)
        {
            base.updateState(vehicle);
            /*UnityEngine.Vector3 pos = vehicle.actor.transform.pos;//相对坐标
            pos = this.mParentPlayer.getPos() + pos;//绝对坐标

            mIsInDangerZone = isInDangerZone(pos);
            if(!mIsInDangerZone)
            {
                curInTime = 0.0f;
            }

            if(mOldIsInDangerZone != mIsInDangerZone)
            {
                mOldIsInDangerZone = mIsInDangerZone;
                if(mOldIsInDangerZone)
                {
                    (this.mParentPlayer as PlayerMain).addDangerNum();
                }
                else
                {
                    (this.mParentPlayer as PlayerMain).subDangerNum();
                }
            }*/
        }
        
        override public void setPos(UnityEngine.Vector3 pos)
        {
            base.setPos(pos);

            UnityEngine.Vector3 _pos = pos;//相对坐标
            _pos = this.mParentPlayer.getPos() + _pos;//绝对坐标
        }
    }
}