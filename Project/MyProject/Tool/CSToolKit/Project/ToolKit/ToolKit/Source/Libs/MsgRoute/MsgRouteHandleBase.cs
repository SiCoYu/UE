namespace SDK.Lib
{
    public class MsgRouteHandleBase : GObject, ICalleeObject
    {
        public MDictionary<int, AddOnceEventDispatch> mId2HandleDic;

        public MsgRouteHandleBase()
        {
            this.mTypeId = "MsgRouteHandleBase";

            this.mId2HandleDic = new MDictionary<int, AddOnceEventDispatch>();
        }

        override public void init()
        {

        }

        override public void dispose()
        {

        }

        public void addMsgRouteHandle(MsgRouteId msgRouteID, MEventDispatchAction<IDispatchObject> handle)
        {
            if(!this.mId2HandleDic.containsKey((int)msgRouteID))
            {
                this.mId2HandleDic[(int)msgRouteID] = new AddOnceEventDispatch();
            }

            this.mId2HandleDic[(int)msgRouteID].addEventHandle(null, handle);
        }

        public void removeMsgRouteHandle(MsgRouteId msgRouteID, MEventDispatchAction<IDispatchObject> handle)
        {
            if (this.mId2HandleDic.containsKey((int)msgRouteID))
            {
                this.mId2HandleDic[(int)msgRouteID].removeEventHandle(null, handle);
            }
        }

        public virtual void handleMsg(IDispatchObject dispObj, uint uniqueId)
        {
            MsgRouteBase msg = dispObj as MsgRouteBase;

            if (this.mId2HandleDic.containsKey((int)msg.mMsgId))
            {
                this.mId2HandleDic[(int)msg.mMsgId].dispatchEvent(msg);
            }
            else
            {
                
            }
        }

        public void call(IDispatchObject dispObj, uint uniqueId)
        {

        }
    }
}