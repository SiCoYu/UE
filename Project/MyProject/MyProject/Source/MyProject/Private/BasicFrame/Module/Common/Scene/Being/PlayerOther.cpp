namespace SDK.Lib
{
	/**
	 * @brief 其它玩家
	 */
	public class PlayerOther : Player
	{
		public PlayerOther()
		{
            this.mTypeId = "PlayerOther";
            this.mEntityType = EntityType.ePlayerOther;
            this.mEntityUniqueId = Ctx.msInstance.mPlayerMgr.genNewStrId();
            this.mMovement = new PlayerOtherMovement(this);
            this.mAttack = new PlayerOtherAttack(this);
        }

        protected override void _onPostInit()
        {
            base._onPostInit();

            //this.hide();

            this.mMovement.init();
            this.mAttack.init();
        }

        override public void initRender()
        {
            if (null == this.mRender)
            {
                this.mRender = new PlayerOtherRender(this);
            }

            this.mRender.init();
        }

        override public void dispose()
        {
            if (null != Ctx.msInstance.mPlayerMgr)
            {
                Ctx.msInstance.mPlayerMgr.removePlayer(this);
            }

            base.dispose();
        }

        override public void putInPool()
        {
            Ctx.msInstance.mPlayerMgr.removePlayer(this);

            base.putInPool();
        }

        override public void onPutInPool()
        {
            if(null != Ctx.msInstance.mBeginnerGuideSys && 
               Ctx.msInstance.mBeginnerGuideSys.isEnableGuide())
            {
                Ctx.msInstance.mBeginnerGuideSys.beatOneEnemy();
            }

            base.onPutInPool();
        }

        override public void autoHandle()
        {
            base.autoHandle();

            Ctx.msInstance.mPlayerMgr.addPlayer(this);
        }

        override public void setPos(UnityEngine.Vector3 pos)
        {
            base.setPos(pos);
            // 如果 Hero ，没有移动的时候，才更新，如果 Hero 在移动，直接通过相机移动更新
            //if (!Ctx.msInstance.mPlayerMgr.isHeroMoving())
            {
                if (null != this.mHud)
                {
                    this.mHud.onPosChanged();
                }
            }
        }
    }
}