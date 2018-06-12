using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 实体组件
     */
    public class EntityRenderCom
    {
        public UnityEngine.Rigidbody mRigidbody;     // 包含的刚体
        public UnityEngine.Rigidbody2D mRigidbody2D;

        public UnityEngine.SpriteRenderer mSpriteRender;//精灵
        public UnityEngine.SpriteRenderer mShadowSpriteRender;//影子精灵
        public UnityEngine.GameObject mBeGodGo;//无敌光环
        public UnityEngine.SpriteRenderer mBeGodSpriteRender;//无敌光环
        public UnityEngine.SpriteRenderer mOutlineSpriteRender;//轮廓
        public UnityEngine.TrailRenderer mNormalTrailRender;//正常速度拖尾
        public UnityEngine.TrailRenderer mFastTrailRender;//分裂速度拖尾
        public UnityEngine.Animator mModelAnimator;    // Model 节点
        public UnityEngine.BoxCollider2D m2DBoxCollider;
        public UnityEngine.CircleCollider2D m2DCircleCollider;
        public UnityEngine.TrailRenderer mOneTrailRenderer;
        public UnityEngine.TrailRenderer mTwoTrailRenderer;
        public UnityEngine.Transform mColliderTrans; // 碰撞转换
        public UnityEngine.GameObject mScoreGo;//加分特效对象

        public EntityRenderCom()
        {
            this.mSpriteRender = null;
            this.mShadowSpriteRender = null;
            this.mBeGodSpriteRender = null;
            this.mOutlineSpriteRender = null;
            this.mNormalTrailRender = null;
            this.mFastTrailRender = null;
        }

        public void findCom(EntityType entityType, GameObject actor)
        {
            this.mRigidbody = UtilEngineWrap.getComByP<UnityEngine.Rigidbody>(actor);
            this.mRigidbody2D = UtilEngineWrap.getComByP<UnityEngine.Rigidbody2D>(actor);

            if (entityType == EntityType.eFlyBullet)
            {
                this.mSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, "bullet"));
                this.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(actor);
                this.m2DBoxCollider = UtilEngineWrap.getComByP<UnityEngine.BoxCollider2D>(actor);
            }
            else if (entityType == EntityType.eSnowBlock)
            {
                this.mSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(actor);
                this.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(actor);
                this.m2DBoxCollider = UtilEngineWrap.getComByP<UnityEngine.BoxCollider2D>(actor);
            }
            else if (entityType == EntityType.eBoomPlane)
            {
                this.mSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, UtilEngineWrap.MODEL_RENDER_NAME));
                this.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(actor);
            }
            else if (entityType == EntityType.eSceneEffect)
            {
                this.mSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, UtilEngineWrap.MODEL_RENDER_NAME));
                this.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(actor);
            }
            else
            {
                this.mSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, UtilEngineWrap.MODEL_RENDER_NAME));
                this.mShadowSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, "model/shadow"));
                this.mBeGodSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, "model/begod"));
                this.mOutlineSpriteRender = UtilEngineWrap.getComByP<UnityEngine.SpriteRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, "model/outline"));
                this.mNormalTrailRender = UtilEngineWrap.getComByP<UnityEngine.TrailRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, UtilEngineWrap.TRIAL_NAME));
                this.mFastTrailRender = UtilEngineWrap.getComByP<UnityEngine.TrailRenderer>(UtilEngineWrap.TransFindChildByPObjAndPath(actor, UtilEngineWrap.TRIAL_1_NAME));
                this.mModelAnimator = UtilEngineWrap.getComByP<UnityEngine.Animator>(actor, UtilEngineWrap.MODEL_NAME);

                //+100特效
                this.mScoreGo = UtilEngineWrap.TransFindChildByPObjAndPath(actor, UtilEngineWrap.MODEL_RENDER_NAME);
                this.mBeGodGo = UtilEngineWrap.TransFindChildByPObjAndPath(actor, "model/begod");

                this.m2DBoxCollider = UtilEngineWrap.getComByP<UnityEngine.BoxCollider2D>(actor);
                this.m2DCircleCollider = UtilEngineWrap.getComByP<UnityEngine.CircleCollider2D>(actor);

                this.mOneTrailRenderer = UtilEngineWrap.getComByP<UnityEngine.TrailRenderer>(actor, UtilEngineWrap.TRIAL_NAME);
                this.mTwoTrailRenderer = UtilEngineWrap.getComByP<UnityEngine.TrailRenderer>(actor, UtilEngineWrap.TRIAL_1_NAME);
                this.mColliderTrans = UtilEngineWrap.TransFindChildTransByPObjAndPath(actor, UtilEngineWrap.COLLIDE_NAME);
            }
        }
    }
}