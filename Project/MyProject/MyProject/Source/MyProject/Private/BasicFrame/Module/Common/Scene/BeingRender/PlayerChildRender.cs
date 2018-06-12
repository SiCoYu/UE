namespace SDK.Lib
{
    public class PlayerChildRender : PlayerRender
    {
        //protected UnityEngine.SkinnedMeshRenderer mNativeRender;

        public PlayerChildRender(SceneEntityBase entity_)
            : base(entity_)
        {
            
        }

        public override void onDestroy()
        {
            UtilEngineWrap.clearSpringJointBody(this.mSelfActor);

            base.onDestroy();
        }

        public override void onPutInPool()
        {
            UtilEngineWrap.clearSpringJointBody(this.mSelfActor);

            base.onPutInPool();
        }

        override protected void _onSelfChanged()
        {
            base._onSelfChanged();

            //this.mModelRender = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.MODEL_RENDER_NAME);
            //this.mModelRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(this.selfGo, UtilEngineWrap.MODEL_RENDER_NAME);

            //if (null != this.mModelRender)
            //{
            //    this.mNativeRender = this.mModelRender.GetComponent<UnityEngine.SkinnedMeshRenderer>();
            //}

            this.setModelMat();

            //AuxClipUserData auxData = UtilEngineWrap.AddComponent<AuxClipUserData>(this.mModelRender);
            //auxData.setUserData(this.mEntity);
            if (!MacroDef.MOBILE_PLATFORM)
                this.setSelfName("" + mEntity.getThisId());

            (this.mEntity as BeingEntity).attachToParentNode(this);     // 关联到父节点上面

            // 设置深度
            UtilEngineWrap.setSpriteRenderSortingLayerBySpriteRenderer(this.mEntityRenderCom.mSpriteRender, this.mLayerDepth);
        }

        // 放到 Pool 中
        override protected void onResReturnToPool()
        {
            base.onResReturnToPool();

            UtilEngineWrap.clearSpringJointBody(this.mSelfActor);
            UtilEngineWrap.SetParent(this.mSelfActor, null);
        }
    }
}