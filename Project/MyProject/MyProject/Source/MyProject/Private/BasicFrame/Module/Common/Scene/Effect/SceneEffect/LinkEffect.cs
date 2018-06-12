namespace SDK.Lib
{
    /**
     * @brief 链接到对象上去的特效，随对象一起移动
     */
    public class LinkEffect : EffectBase
    {
        protected SceneEntityBase mLinkedEntity;       // 连接的对象，测试使用

        public LinkEffect()
        {
            this.mEntityType = EntityType.eLinkEffect;
        }

        public SceneEntityBase getLinkedEntity()
        {
            return this.mLinkedEntity;
        }

        public void setLinkedEntity(SceneEntityBase value)
        {
            this.mLinkedEntity = value;
        }

        override public void setTableId(int tableId)
        {
            base.setTableId(tableId);
            //UtilEngineWrap.adjustEffectRST((mRender as EffectSpriteRender).spriteRender.selfGo.transform);
        }

        override public void onPutInPool()
        {
            base.onPutInPool();

            this.mLinkedEntity = null;
        }
    }
}