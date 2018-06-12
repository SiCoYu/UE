using UnityEngine;

namespace SDK.Lib
{
    public class BeingEntityRender : EntityRenderBase
    {
        protected string mResPath;  // 资源目录

        protected AuxScenePrefabLoader mAuxPrefabLoader;
        protected AuxTextureLoader mAuxTextureLoader;
        protected AuxUnityAtlasLoader mPlaneSpriteloader;  // 飞机
        protected AuxUnityAtlasLoader mShadowSpriteloader; // 阴影

        protected string mPlaneSpritePath;
        protected string mPlaneSpriteName;
        protected string mShadowSpritePath;
        protected string mShadowSpriteName;

        /**
         * @brief 资源加载之类的基本操作写在这里
         */
        public BeingEntityRender(SceneEntityBase entity_)
            : base(entity_)
        {
            this.mPlaneSpritePath = "";
            this.mShadowSpritePath = "";
        }

        public void setResPath(string path)
        {
            this.mResPath = path;
        }

        protected override void findCom()
        {
            base.findCom();

            this.mEntityRenderCom = this.mAuxPrefabLoader.getEntityRenderCom();
        }

        override public void onDestroy()
        {
            this.releaseRes();

            base.onDestroy();
        }

        override public void onPutInPool()
        {
            this.releaseRes();

            base.onPutInPool();
        }

        // 仅仅是释放资源
        virtual protected void releaseRes()
        {
            this.onResReturnToPool();

            if(null != this.mAuxPrefabLoader)
            {
                AssetStrIdBufferObjectFactory.deleteObject(this.mAuxPrefabLoader);
                this.mAuxPrefabLoader = null;
            }

            if(null != this.mPlaneSpriteloader)
            {
                AssetStrIdBufferObjectFactory.deleteObject(this.mPlaneSpriteloader);
                this.mPlaneSpriteloader = null;
            }

            if(null != this.mShadowSpriteloader)
            {
                AssetStrIdBufferObjectFactory.deleteObject(this.mShadowSpriteloader);
                this.mShadowSpriteloader = null;
            }

            if(null != this.mAuxTextureLoader)
            {
                AssetStrIdBufferObjectFactory.deleteObject(this.mAuxTextureLoader);
                this.mAuxTextureLoader = null;
            }
        }

        override public void onClipShow()
        {
            // 进入显示的时候必然是空，这里再判断一次
            if (null == this.mAuxPrefabLoader)
            {
                this.load();
            }
        }

        override public void onClipHide()
        {
            this.releaseRes();
            this.setSelfActor(null);
        }

        override public void updateLocalTransform()
        {
            if (this.mSelfActor)
            {
                if (this.mIsPosDirty)
                {
                    this.mIsPosDirty = false;

                    // 只有自己才是物理移动
                    if (MacroDef.PHYSIX_MOVE && 
                        (null != this.mEntityRenderCom.mRigidbody || this.mEntityRenderCom.mRigidbody2D) && EntityType.ePlayerMainChild == this.mEntity.getEntityType())
                    {
                        UtilEngineWrap.setRigidbodyPos(this.mEntityRenderCom.mRigidbody, this.mEntity.getPos());
                        UtilEngineWrap.setRigidbody2DPos(this.mEntityRenderCom.mRigidbody2D, this.mEntity.getPos());
                    }
                    else
                    {
                        UtilEngineWrap.setPos(this.mSelfActor.transform, this.mEntity.getPos());
                    }
                    // 内部 2D 物理组件总是会移动，因此重置一下
                    UtilEngineWrap.resetRST(this.mEntityRenderCom.mColliderTrans);
                }
                if (this.mIsRotDirty)
                {
                    this.mIsRotDirty = false;

                    UtilEngineWrap.setRot(this.mSelfActor.transform, this.mEntity.getRotate());
                }
                if (this.mIsScaleDirty)
                {
                    this.mIsScaleDirty = false;

                    //UtilEngineWrap.setScale(this.mSelfActor.transform, this.mEntity.getScale());
                }
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
                this.mAuxPrefabLoader.setIsInsNeedCoroutine(true);
                this.mAuxPrefabLoader.setIsInitOrientPos(true);
                this.mAuxPrefabLoader.setIsFakePos(true);
            }

            this.mAuxPrefabLoader.asyncLoad(this.mResPath, null, this.onResLoaded);
        }

        virtual public void onResLoaded(IDispatchObject dispObj, uint uniqueId)
        {
            this.setSelfActor(this.mAuxPrefabLoader.getGameObject());

            this.loadSprite();
        }

        override protected void _onSelfChanged()
        {
            base._onSelfChanged();

            //characterController = ((UnityEngine.GameObject)this.gameObject()).GetComponent<UnityEngine.CharacterController>();
            //if (null == characterController)
            //{
            //    characterController = ((UnityEngine.GameObject)this.gameObject()).AddComponent<UnityEngine.CharacterController>();
            //}

            //this.mModel = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.MODEL_NAME);
        }

        virtual protected void loadSprite()
        {
            if (!string.IsNullOrEmpty(this.mPlaneSpritePath))
            {
                if (null == this.mPlaneSpriteloader)
                {
                    this.mPlaneSpriteloader = AssetStrIdBufferObjectFactory.newObject<AuxUnityAtlasLoader>(this.mPlaneSpritePath);
                }

                this.mPlaneSpriteloader.asyncLoad(
                    this.mPlaneSpritePath,
                    null,
                    this.onPlaneSpriteLoaded
                    );
            }

            if (!string.IsNullOrEmpty(this.mShadowSpritePath))
            {
                if (null == this.mShadowSpriteloader)
                {
                    this.mShadowSpriteloader = AssetStrIdBufferObjectFactory.newObject<AuxUnityAtlasLoader>(this.mShadowSpritePath);
                }

                this.mShadowSpriteloader.asyncLoad(
                    this.mShadowSpritePath,
                    null,
                    this.onShadowSpriteLoaded
                    );
            }
        }

        virtual public void onPlaneSpriteLoaded(IDispatchObject dispObj, uint uniqueId)
        {
            UtilEngineWrap.setSpriteRendererSprite(this.mEntityRenderCom.mSpriteRender, this.mPlaneSpriteloader.getSprite(this.mPlaneSpriteName));
        }

        public void onShadowSpriteLoaded(IDispatchObject dispObj, uint uniqueId)
        {
            UtilEngineWrap.setSpriteRendererSprite(this.mEntityRenderCom.mShadowSpriteRender, this.mShadowSpriteloader.getSprite(this.mShadowSpriteName));
        }

        override public Bounds getBounds()
        {
            if (null == this.mEntityRenderCom.mModelAnimator)
            {
                //this.mModel = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.MODEL_NAME);
                this.mEntityRenderCom.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(this.mSelfActor, UtilEngineWrap.MODEL_NAME);
            }

            return UtilEngineWrap.getComByP<MeshFilter>(this.mEntityRenderCom.mModelAnimator.gameObject).mesh.bounds;
        }

        // 获取 Model GameObject
        virtual public GameObject getModelObject()
        {
            if (null == this.mEntityRenderCom.mModelAnimator)
            {
                //this.mModel = UtilEngineWrap.TransFindChildByPObjAndPath(this.selfGo, UtilEngineWrap.MODEL_NAME);
                this.mEntityRenderCom.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(this.mSelfActor, UtilEngineWrap.MODEL_NAME);
            }

            //return this.mModel;
            return this.mEntityRenderCom.mModelAnimator.gameObject;
        }

        override public void setTexture(string path)
        {
            if (null == this.mAuxTextureLoader) {
                this.mAuxTextureLoader = AssetStrIdBufferObjectFactory.newObject<AuxTextureLoader>("", false);
            }

            this.mAuxTextureLoader.asyncLoad(
                path,
                null,
                this.onTextureLoaded
                );
        }

        override public void setTexTile(TileInfo tileInfo)
        {
            this.setModelTexTile();
        }

        public void onTextureLoaded(IDispatchObject dispObj, uint uniqueId)
        {
            if (this.mAuxTextureLoader.hasSuccessLoaded()) {
                this.setModelMat();
            } else {
                this.mAuxTextureLoader.dispose();
                this.mAuxTextureLoader = null;
            }
        }

        protected void setModelMat()
        {
            if (null != this.mEntityRenderCom.mSpriteRender &&
                null != this.mAuxTextureLoader &&
                this.mAuxTextureLoader.hasSuccessLoaded())
            {
                UtilEngineWrap.setGameObjectMainTexture(this.mEntityRenderCom.mSpriteRender.gameObject, this.mAuxTextureLoader.getTexture());
            }
        }

        protected void setModelTexTile()
        {
            if (null != this.mEntityRenderCom.mSpriteRender)
            {
                UtilEngineWrap.setGoTile(this.mEntityRenderCom.mSpriteRender.gameObject, (this.mEntity as BeingEntity).getTileInfo());
            }
        }
    }
}