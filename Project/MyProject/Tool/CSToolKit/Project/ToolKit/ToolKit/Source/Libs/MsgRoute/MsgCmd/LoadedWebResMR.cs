namespace SDK.Lib
{
    public class LoadedWebResMR : MsgRouteBase
    {
        public ITask mTask;

        public LoadedWebResMR()
        {
            this.setMsgTypeAndsetMsgId(MsgRouteType.eMRT_BASIC, MsgRouteId.eMRID_LoadedWebRes);
        }

        override public void onPutInPool()
        {
            this.mTask = null;
        }
    }
}
