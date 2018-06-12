namespace SDK.Lib
{
    public class PlayerMainRender : PlayerRender
    {
        public PlayerMainRender(SceneEntityBase entity_)
            : base(entity_)
        {

        }

        override public void onInit()
        {
            base.onInit();

            this.mResPath = "World/Model/PlayerMainPlace.prefab";
            this.mPlaneSpritePath = "";
            this.mShadowSpritePath = "";
        }

        override protected void _onSelfChanged()
        {
            base._onSelfChanged();

            //GameObject collide = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.COLLIDE_NAME);
            //AuxPlayerMainUserData auxData = UtilEngineWrap.AddComponent<AuxPlayerMainUserData>(collide);
            //AuxPlayerMainUserData auxData = UtilEngineWrap.AddComponent<AuxPlayerMainUserData>(this.selfGo);
            //auxData.setUserData(this.mEntity);

            //UtilEngineWrap.setLayer(this.selfGo, "PlayerMain");

            Ctx.msInstance.mCamSys.setCameraActor(this.mEntity);
        }

        override public void show()
        {
            if (!IsVisible())
            {
                UtilEngineWrap.SetActive(this.mSelfActor, true);
            }
        }

        override public void hide()
        {
            if (this.IsVisible())
            {
                UtilEngineWrap.SetActive(this.mSelfActor, false);
            }
        }

        // 资源加载
        override public void load()
        {
            if (null == this.mAuxPrefabLoader)
            {
                this.mAuxPrefabLoader = AssetStrIdBufferObjectFactory.newObject<AuxScenePrefabLoader>(this.mResPath, true);
                this.mAuxPrefabLoader.setEntityType(this.mEntity.getEntityType());
                this.mAuxPrefabLoader.setDestroySelf(true);
                this.mAuxPrefabLoader.setIsNeedInsRes(true);
                this.mAuxPrefabLoader.setIsInsNeedCoroutine(false);
                this.mAuxPrefabLoader.setIsInitOrientPos(true);
                this.mAuxPrefabLoader.setIsFakePos(true);
            }

            // 这种直接同步加载
            this.mAuxPrefabLoader.syncLoad(
                this.mResPath,
                null,
                this.onResLoaded
                );
        }

        override public void updateLocalTransform()
        {
            if (null != this.mSelfActor)
            {
                if (this.mIsPosDirty)
                {
                    this.mIsPosDirty = false;

                    UtilEngineWrap.setPos(this.mSelfActor.transform, this.mEntity.getPos());
                }
            }
        }
    }
}