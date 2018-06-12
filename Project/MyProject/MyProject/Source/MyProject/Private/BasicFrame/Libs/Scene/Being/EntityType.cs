namespace SDK.Lib
{
    public enum EntityType
    {
        ePlayerMain = 0,
        ePlayerOther = 1,
        ePlayerMainChild = 2,
        ePlayerOtherChild = 3,
        eRobot = 4,
        eSnowBlock = 5,
        ePlayerTarget = 6,
        eAbandonPlane = 7,      // 被遗弃的飞机
        eComputerBall = 8,
        eFlyBullet = 9,         // 子弹
        eFlyBulletFlock = 10,   // 子弹 Flock
        eCount = 11,
        eBoomPlane = 12,        // 爆炸的飞机
        eScoreEffect = 13,      // 加分特效
        eLinkEffect = 14,       // 链接特效
        eMoveEffect = 15,       // 移动特效
        eSceneEffect = 16,      // 场景特效
        eMeteStone = 17,      // 陨石
        eGroundEntity = 18,

        // 从 1000 - 1100 子弹
        eFlyBulletFlock_A = 1000,    // 子弹 Flock
        eFlyBulletFlock_B = 1001,    // 子弹 Flock
        eFlyBulletFlock_C = 1002,    // 子弹 Flock
        eFlyBulletFlock_D = 1003,    // 子弹 Flock
    }
}