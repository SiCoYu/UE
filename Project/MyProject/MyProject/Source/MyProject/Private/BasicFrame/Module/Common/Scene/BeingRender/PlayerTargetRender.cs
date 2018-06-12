namespace SDK.Lib
{
    public class PlayerTargetRender : PlayerRender
    {
        public PlayerTargetRender(SceneEntityBase entity_)
            : base(entity_)
        {

        }

        override public void onInit()
        {
            base.onInit();

            this.mResPath = "World/Model/PathDot.prefab";
        }

        override protected void _onSelfChanged()
        {
            base._onSelfChanged();
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
    }
}