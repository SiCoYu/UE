namespace SDK.Lib
{
    public class PlayerMainChildRender : PlayerChildRender
    {
        public PlayerMainChildRender(SceneEntityBase entity_)
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
            //AuxPlayerMainChildUserData auxData = UtilEngineWrap.AddComponent<AuxPlayerMainChildUserData>(collide);
            //auxData.setUserData(this.mEntity);

            if (MacroDef.DEBUG_NOTNET)
            {
                AuxPlayerMainChildUserData auxData = UtilEngineWrap.AddComponent<AuxPlayerMainChildUserData>(this.mSelfActor);
                auxData.setUserData(this.mEntity);
            }

            //UnityEngine.GameObject model = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.MODEL_NAME);
            if (null != (this.mEntity as Player).mAnimatorControl)
            {
                //(this.mEntity as Player).mAnimatorControl.setAnimator(UtilEngineWrap.getComByP<UnityEngine.Animator>(model));
                (this.mEntity as Player).mAnimatorControl.setAnimator(this.mEntityRenderCom.mModelAnimator);
            }

            //UtilEngineWrap.setSprite(this.mSpriteRender, Ctx.msInstance.mSnowBallCfg.planes[(this.mEntity as PlayerChild).mParentPlayer.mPlaneIndex].mPath);
            //UtilEngineWrap.setSprite(this.mShadowSpriteRender, Ctx.msInstance.mSnowBallCfg.planes[(this.mEntity as PlayerChild).mParentPlayer.mPlaneIndex].mShadow);

            //UtilEngineWrap.setLayer(this.selfGo, "PlayerMainChild");
        }

        override protected void onResReturnToPool()
        {
            base.onResReturnToPool();

            if (null != this.mSelfActor)
            {
                // 关闭组件
                //UtilEngineWrap.enableSpriteRenderComponentBy(this.mModelRender, false);
                UtilEngineWrap.enableSpriteRenderComponentBySpriteRender(this.mEntityRenderCom.mSpriteRender, false);
                //UtilEngineWrap.enableAnimatorComponent(this.mModel, false);
                UtilEngineWrap.enableAnimatorComponentByAnimator(this.mEntityRenderCom.mModelAnimator, false);
                //UtilEngineWrap.enableCollider<UnityEngine.SphereCollider>(this.mSelfActor, false);
                if (MacroDef.DEBUG_NOTNET)
                {
                    UtilEngineWrap.enableCollider2DByCollider<UnityEngine.BoxCollider2D>(this.mEntityRenderCom.m2DBoxCollider, false);
                }

                //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(this.mSelfActor, false);
                //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(UtilEngineWrap.TransFindChildByPObjAndPath(this.mSelfActor, UtilEngineWrap.COLLIDE_NAME), false);

                //UtilEngineWrap.enableRigidbodyComponent(this.mSelfActor, false);

                // 关闭拖尾
                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mOneTrailRenderer, false);
                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mTwoTrailRenderer, false);
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
                //UtilEngineWrap.enableCollider<UnityEngine.SphereCollider>(UtilEngineWrap.TransFindChildByPObjAndPath(this.mSelfActor, UtilEngineWrap.COLLIDE_NAME), true);

                //if (((this.mEntity as PlayerMainChild).mParentPlayer as PlayerMain).mMutilRigidCalcPolicy.checkPolicy(this.mEntity as BeingEntity))
                //{
                //    UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(this.mSelfActor, true);
                //}
                
                //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(UtilEngineWrap.TransFindChildByPObjAndPath(this.mSelfActor, UtilEngineWrap.COLLIDE_NAME), true);

                //UtilEngineWrap.enableRigidbodyComponent(this.mSelfActor, true);

                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mOneTrailRenderer, true);
                UtilEngineWrap.enableTrailRendererComponentByTrailRenderer(this.mEntityRenderCom.mOneTrailRenderer, false);

                if (MacroDef.DEBUG_NOTNET)
                {
                    //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(this.mSelfActor, true);
                    UtilEngineWrap.enableCollider2DByCollider<UnityEngine.BoxCollider2D>(this.mEntityRenderCom.m2DBoxCollider, true);
                }
            }
        }

        override public void enableRigid(bool enable)
        {
            //UtilEngineWrap.enableCollider2D<UnityEngine.BoxCollider2D>(this.mSelfActor, enable);
        }

        public void setSpringJointDistance(float distance)
        {
            //动态更新弹簧关节的Distance
            UnityEngine.SpringJoint2D springJoint2D = this.mSelfActor.GetComponent<UnityEngine.SpringJoint2D>();
            if (null != springJoint2D)
            {
                springJoint2D.distance = distance < 0.005f ? 0.005f : distance;
            }
        }
    }
}