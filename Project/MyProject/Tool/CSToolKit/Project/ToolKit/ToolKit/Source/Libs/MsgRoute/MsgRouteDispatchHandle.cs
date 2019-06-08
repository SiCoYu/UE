namespace SDK.Lib
{
    public class MsgRouteDispatchHandle
    {
        protected EventDispatchGroup mEventDispatchGroup;

        public MsgRouteDispatchHandle()
        {
            this.mEventDispatchGroup = new EventDispatchGroup();
        }

        virtual public void init()
        {

        }

        virtual public void dispose()
        {

        }

        public void addRouteHandle(int groupID, MsgRouteHandleBase pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            this.mEventDispatchGroup.addEventHandle(groupID, pThis, handle, eventId);
        }

        public void removeRouteHandle(int groupID, MsgRouteHandleBase pThis, MEventDispatchAction<IDispatchObject> handle, uint eventId)
        {
            this.mEventDispatchGroup.removeEventHandle(groupID, pThis, handle, eventId);
        }

        public virtual void handleMsg(MsgRouteBase msg)
        {
            if(this.mEventDispatchGroup.hasEventHandle((int)msg.mMsgType))
            {
                this.mEventDispatchGroup.dispatchEvent((int)msg.mMsgType, msg);
            }
            else
            {
                
            }
        }
    }
}