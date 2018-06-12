namespace SDK.Lib
{
    public class PlayerOtherChildRender : PlayerChildRender
    {
        public PlayerOtherChildRender(SceneEntityBase entity_)
            : base(entity_)
        {

        }

        override public void onInit()
        {
            base.onInit();

            this.mResPath = (this.mEntity as BeingEntity).getPrefabPath();

            UtilLogic.convFullPath2AtlasPathAndName(this.mPlaneSpritePath, ref this.mLayerDepth);
        }

        override protected void _onSelfChanged()
        {
            base._onSelfChanged();

            //UnityEngine.GameObject collide = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.COLLIDE_NAME);
            //AuxPlayerOtherChildUserData auxData = UtilEngineWrap.AddComponent<AuxPlayerOtherChildUserData>(collide);

            if (MacroDef.DEBUG_NOTNET)
            {
                AuxPlayerOtherChildUserData auxData = UtilEngineWrap.AddComponent<AuxPlayerOtherChildUserData>(this.mSelfActor);
                auxData.setUserData(this.mEntity);
            }

            //UtilEngineWrap.setSprite(this.mSpriteRender, Ctx.msInstance.mSnowBallCfg.planes[(this.mEntity as PlayerChild).mParentPlayer.mPlaneIndex].mPath);
            //UtilEngineWrap.setSprite(this.mShadowSpriteRender, Ctx.msInstance.mSnowBallCfg.planes[(this.mEntity as PlayerChild).mParentPlayer.mPlaneIndex].mShadow);

            //UtilEngineWrap.setLayer(this.selfGo, "PlayerOtherChild");
        }

        override protected void onResReturnToPool()
        {
            base.onResReturnToPool();

            if (null != this.mSelfActor)
            {
                // 关闭组件
                UtilEngineWrap.enableSpriteRenderComponentBySpriteRender(this.mEntityRenderCom.mSpriteRender, false);
                UtilEngineWrap.enableSpriteRenderComponentBySpriteRender(this.mEntityRenderCom.mShadowSpriteRender, false);
                UtilEngineWrap.enableAnimatorComponentByAnimator(this.mEntityRenderCom.mModelAnimator, false);
                //UtilEngineWrap.enableCollider<UnityEngine.SphereCollider>(this.mSelfActor, false);
                //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(this.mSelfActor, false);

                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mOneTrailRenderer, false);
                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mTwoTrailRenderer, false);

                if (MacroDef.DEBUG_NOTNET)
                {
                    UtilEngineWrap.enableCollider2DByCollider<UnityEngine.BoxCollider2D>(this.mEntityRenderCom.m2DBoxCollider, false);
                }
            }
        }

        override protected void onResGetFromPool()
        {
            base.onResGetFromPool();

            if (null != this.mSelfActor)
            {
                // 打开组件
                UtilEngineWrap.enableSpriteRenderComponentBySpriteRender(this.mEntityRenderCom.mSpriteRender, true);
                UtilEngineWrap.enableSpriteRenderComponentBySpriteRender(this.mEntityRenderCom.mShadowSpriteRender, true);
                UtilEngineWrap.enableAnimatorComponentByAnimator(this.mEntityRenderCom.mModelAnimator, true);
                //UtilEngineWrap.enableCollider<UnityEngine.SphereCollider>(this.mSelfActor, true);
                //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(this.mSelfActor, true);

                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mOneTrailRenderer, true);
                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mTwoTrailRenderer, false);

                if (MacroDef.DEBUG_NOTNET)
                {
                    UtilEngineWrap.enableCollider2DByCollider<UnityEngine.BoxCollider2D>(this.mEntityRenderCom.m2DBoxCollider, true);
                }
            }
        }
    }
}