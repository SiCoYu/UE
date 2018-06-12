namespace SDK.Lib
{
    public class PlayerMainAttack : BeingEntityAttack
    {
        public PlayerMainAttack(BeingEntity entity)
            : base(entity)
        {

        }

        override public void overlapToEnter(BeingEntity bBeingEntity, UnityEngine.Collision collisionInfo)
        {
            if (UtilEngineWrap.isInFakePos(this.mEntity.getPos()))
            {
                return;
            }

            if (bBeingEntity.getEntityType() == EntityType.eSnowBlock)
            {
                this.eateSnowBlock(bBeingEntity);
            }
            else if (bBeingEntity.getEntityType() == EntityType.ePlayerOther)
            {
                this.eatePlayerOther(bBeingEntity);
            }
            else if (bBeingEntity.getEntityType() == EntityType.eRobot)
            {
                EatState state = EatState.Nothing_Happen;

                Player bPlayer = bBeingEntity as Player;

                if (this.mEntity.canEatOther(bBeingEntity))
                {
                    state = EatState.Eat_Other;
                }
                else if (bBeingEntity.canEatOther(this.mEntity))
                {
                    state = EatState.Eaten_ByOther;
                }
            }
        }

        // 雪块
        public void eateSnowBlock(BeingEntity bBeingEntity)
        {
            //this.mEntity.cellCall("eatSnowBlock", bBeingEntity.getThisId());
        }

        // 玩家之间互吃
        public void eatePlayerOther(BeingEntity bBeingEntity)
        {
            bool otherIsGod = bBeingEntity.getIsGod();

            if (this.mEntity.canEatOther(bBeingEntity) && otherIsGod)
            {
                //this.mEntity.cellCall("eatSnowBlock", bBeingEntity.getThisId());
            }
        }
    }
}