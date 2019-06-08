namespace SDK.Lib
{
    public class SocketOpenedMR : MsgRouteBase
    {
        public SocketOpenedMR()
        {
            this.setMsgTypeAndsetMsgId(MsgRouteType.eMRT_BASIC, MsgRouteId.eMRID_SocketOpened);
        }
    }
}