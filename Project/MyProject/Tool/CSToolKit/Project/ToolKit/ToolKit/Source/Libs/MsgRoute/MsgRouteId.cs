namespace SDK.Lib
{
    public enum MsgRouteId
    {
        eMRIDNULL,      // 默认值

        eMRID_SocketOpened,      // socket Opened
        eMRID_SocketClosed,      // socket Closed
        eMRID_LoadedWebRes,      // web 资源加载完成
        eMRID_ThreadLog,         // 线程打日志

        eMRID_NewItem,
        eMRID_JoinTeam,
        eMRID_AOIJoinTeam,
        eMRID_MoveTeam,
        eMRID_NewTrangle,

        eMRID_RemoveTrangle,
        eMRID_MoveTeamBullet,
        eMRID_TeamShooteMRID_NewItem,
        eMRID_TeamShoot,
        eMRID_BulletTimeOut,
        eMRID_HitTrangleCommand,
        eMRID_HitItemCommand,
        eMRID_BumpMeteStoneCommand,
        eMRID_TrangleInDangerZone,
        eMRID_TrangleOutDangerZone,
        eMRID_TrangleTeamLeave,
        eMRID_BatchAddEnergyPlane,
        eMRID_BatchRemovePlane,
        eMRID_NewTeamShoot,
    }
}