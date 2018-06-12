using UnityEngine;

namespace SDK.Lib
{
    public class GroundEntityRender : BeingEntityRender
    {
        public GroundEntityRender(SceneEntityBase entity_)
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

        override public void load()
        {
            if (null == this.mAuxPrefabLoader)
            {
                this.mAuxPrefabLoader = new AuxScenePrefabLoader();
                this.mAuxPrefabLoader.setDestroySelf(false);
                this.mAuxPrefabLoader.setIsNeedInsRes(true);
                this.mAuxPrefabLoader.asyncLoad(
                    (this.mEntity as GroundEntity).getLevelXmlActorItem().mPrefabPath, 
                    null, 
                    this.onResLoaded
                    );
            }
        }

        override public void onResLoaded(IDispatchObject dispObj, uint eventId)
        {
            if (this.mAuxPrefabLoader.hasSuccessIns())
            {
                GameObject parentActor = UtilEngineWrap.findChildFromRootByName((this.mEntity as GroundEntity).getLevelXmlActorItem().mParentActorPath);

                (this.mEntity as GroundEntity).getLevelXmlActorItem().initActor(this.mAuxPrefabLoader.getSelfActor(), parentActor);

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("GroundEntityRender::onResLoaded, load, ActorName = {0}", (this.mEntity as GroundEntity).getLevelXmlActorItem().mName), LogTypeId.eLogTwoDSceneMgr);
                }
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("GroundEntityRender::onResLoaded, fail, ActorName = {0}", (this.mEntity as GroundEntity).getLevelXmlActorItem().mName), LogTypeId.eLogTwoDSceneMgr);
                }
            }
        }
    }
}