namespace SDK.Lib
{
    public class PlayerMainChildAttack : PlayerChildAttack
    {
        public PlayerMainChildAttack(BeingEntity entity)
            : base(entity)
        {

        }

        override public void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
        {
            
        }

        override public void overlapToStay(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
        {
            if (EntityType.ePlayerOther == bBeingEntity.getEntityType())
            {
                this.eatPlayerOther(bBeingEntity);
            }
        }

        override public void overlapToExit(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
        {
            
        }

        override public void overlapToEnter2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
        {
            if (EntityType.eFlyBullet == bBeingEntity.getEntityType())
            {
                // 如果是 FlyBullet ，直接转向 FlyBullet 处理
                bBeingEntity.overlapToEnter2D(this.mEntity, collisionInfo);
            }
            else if(EntityType.eMeteStone == bBeingEntity.getEntityType())
            {
                // 转到陨石统一处理
                bBeingEntity.overlapToEnter2D(this.mEntity, collisionInfo);
            }
        }

        override public void overlapToStay2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
        {
            
        }

        override public void overlapToExit2D(BeingEntity bBeingEntity, UnityEngine.Collision2D collisionInfo)
        {

        }
        
        // 玩家之间互吃
        public void eatPlayerOther(BeingEntity bBeingEntity)
        {
            bool otherIsGod = bBeingEntity.getIsGod();

            if (this.mEntity.canEatOther(bBeingEntity) && otherIsGod)
            {
                bBeingEntity.setClientDispose(true);
                //this.mEntity.cellCall("eatSnowBlock", bBeingEntity.getThisId());
            }
        }
        
        // 碰撞 PlayerMainChild
        public void eatPlayerMainChild(BeingEntity bBeingEntity)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("PlayerMainChildAttack::eatPlayerMainChild, enter eatPlayerMainChild", LogTypeId.eLogMergeBug);
            }
        }
    }
}