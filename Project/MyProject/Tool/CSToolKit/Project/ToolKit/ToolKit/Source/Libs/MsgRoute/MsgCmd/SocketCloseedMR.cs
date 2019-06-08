namespace SDK.Lib
{
    public class SocketCloseedMR : MsgRouteBase
    {
        public SocketCloseedMR()
        {
            this.setMsgTypeAndsetMsgId(MsgRouteType.eMRT_BASIC, MsgRouteId.eMRID_SocketClosed);
        }
    }
}