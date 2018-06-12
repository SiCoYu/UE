using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 这个场景特效管理器
     */
    public class SceneEffectMgr : EntityMgrBase
    {
        public void addEffect(EffectBase effect, float priority = 0.0f)
        {
            this._addObject(effect, priority);
        }

        public void removeEffect(EffectBase effect)
        {
            this._removeObject(effect);
        }

        override protected void _onTickExec(float delta, TickMode tickMode)
        {
            base._onTickExec(delta, tickMode);
        }

        public EffectBase createAndAdd(EffectType type, EffectRenderType renderType)
        {
            EffectBase effect = null;

            if(EffectType.eLinkEffect == type)
            {
                effect = EntityNumIdBufferObjectFactory.newObject<LinkEffect>(EntityType.eLinkEffect, true);
            }
            else if (EffectType.eMoveEffect == type)
            {
                effect = new MoveEffect();
                effect = EntityNumIdBufferObjectFactory.newObject<MoveEffect>(EntityType.eMoveEffect, true);
            }
            else if (EffectType.eSceneEffect == type)
            {
                effect = EntityNumIdBufferObjectFactory.newObject<SceneEffect>(EntityType.eSceneEffect, true);
            }

            effect.setEffectType(type);
            effect.setEffectRenderType(renderType);
            effect.init();

            return effect;
        }

        //public void removeAndDestroy(EffectBase effect)
        //{
        //    this.delObject(effect);
        //    effect.dispose();
        //}

        // 添加连接特效，固定不动
        public LinkEffect addLinkEffect(int id, GameObject pntGO_ = null, bool bAutoRemove = true, bool bLoop = false, bool bPlay = true)
        {
            LinkEffect effect = this.createAndAdd(EffectType.eLinkEffect, EffectRenderType.eShurikenEffectRender) as LinkEffect;

            effect.setPnt(pntGO_);
            effect.setLoop(bLoop);
            effect.setTableId(id);
            effect.setIsAutoRemove(bAutoRemove);

            if (bPlay)
            {
                effect.play();
            }

            return effect;
        }

        // 添加移动特效
        public MoveEffect addMoveEffect(int id, GameObject pntGO_, Vector3 srcPos, Vector3 destPos, float moveTime, bool bAutoRemove = true, bool bLoop = false, bool bPlay = true)
        {
            MoveEffect effect = this.createAndAdd(EffectType.eMoveEffect, EffectRenderType.eSpriteEffectRender) as MoveEffect;

            effect.setPnt(pntGO_);
            effect.setLoop(bLoop);
            effect.setTableId(id);
            effect.setSrcPos(srcPos);
            effect.setDestPos(destPos);
            effect.setEffectMoveTime(moveTime);
            effect.setIsAutoRemove(bAutoRemove);

            if (bPlay)
            {
                effect.play();
            }

            return effect;
        }

        // 添加一个场景特效
        public SceneEffect addSceneEffect(int id, GameObject pntGO_, bool bAutoRemove = true, bool bLoop = false, bool bPlay = true)
        {
            SceneEffect effect = this.createAndAdd(EffectType.eSceneEffect, EffectRenderType.eSpriteEffectRender) as SceneEffect;

            effect.setPnt(pntGO_);
            effect.setLoop(bLoop);
            effect.setTableId(id);
            effect.setIsAutoRemove(bAutoRemove);

            if (bPlay)
            {
                effect.play();
            }

            return effect;
        }
    }
}