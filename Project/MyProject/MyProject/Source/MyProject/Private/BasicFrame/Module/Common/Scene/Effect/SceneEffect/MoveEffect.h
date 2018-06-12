using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 可以移动的特效
     */
    public class MoveEffect : EffectBase
    {
        protected EffectMoveControl mMoveControl;
        protected Vector3 mDestPos;                // 终点
        protected EventDispatch mMoveDestEventDispatch;         // 移动到目标事件分发，注意不是
        protected float mEffectMoveTime;

        public MoveEffect()
        {
            this.mEntityType = EntityType.eMoveEffect;
            this.mMoveControl = new EffectMoveControl(this);
            this.mMoveDestEventDispatch = new AddOnceAndCallOnceEventDispatch();
        }

        public EventDispatch getMoveDestEventDispatch()
        {
            return this.mMoveDestEventDispatch;
        }

        public Vector3 getSrcPos()
        {
            return this.gameObject().transform.localPosition;
        }

        public void setSrcPos(Vector3 value)
        {
            UtilEngineWrap.setPos(this.gameObject().transform, value);
        }

        public Vector3 getDestPos()
        {
            return this.mDestPos;
        }

        public void setDestPos(Vector3 value)
        {
            this.mDestPos = value;
        }

        public float getEffectMoveTime()
        {
            return this.mEffectMoveTime;
        }

        public void setEffectMoveTime(float value)
        {
            this.mEffectMoveTime = value;
        }

        override public void onTick(float delta, TickMode tickMode)
        {
            base.onTick(delta, tickMode);
        }

        override public void setTableId(int tableId)
        {
            base.setTableId(tableId);
            //UtilEngineWrap.adjustEffectRST((mRender as EffectSpriteRender).spriteRender.selfGo.transform);
        }

        override public void play()
        {
            this.mMoveControl.moveToDest(this.gameObject().transform.localPosition, mDestPos, mEffectMoveTime, onMoveToDest);
            base.play();
        }

        public void syncUpdate()        // 加载资源
        {
            (this.mRender as SpriteEffectRender).getSpriteAniRender().syncUpdateCom();
        }

        public override void dispose()
        {
            this.mMoveDestEventDispatch.clearEventHandle();
            this.mMoveDestEventDispatch = null;

            base.dispose();
        }

        // 特效移动到终点
        protected void onMoveToDest(NumAniBase ani)
        {
            this.mMoveDestEventDispatch.dispatchEvent(this);
        }

        override public void addMoveDestEventHandle(MEventDispatchAction<IDispatchObject> dispObj)
        {
            this.mMoveDestEventDispatch.addEventHandle(null, dispObj);
        }
    }
}