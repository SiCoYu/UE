namespace SDK.Lib
{
    public class MsgRouteBase : IDispatchObject
    {
        public MsgRouteType mMsgType;
        public MsgRouteId mMsgId;          // 只需要一个 Id 就行了
        public bool mIsMainThreadImmeHandle;    // 是否主线程立即处理消息
        protected bool mIsUsePool;

        public MsgRouteBase()
        {
            this.mMsgType = MsgRouteType.eMRT_BASIC;
            this.mMsgId = MsgRouteId.eMRIDNULL;

            this.mIsMainThreadImmeHandle = true;
        }

        public void setMsgTypeAndsetMsgId(MsgRouteType msgType, MsgRouteId msgId)
        {
            this.mMsgType = msgType;
            this.mMsgId = msgId;
        }

        virtual public void onPutInPool()
        {

        }

        virtual public void onGetFromPool()
        {

        }

        public void putInPool()
        {
            this.onPutInPool();
        }

        public void getFromPool()
        {
            this.onGetFromPool();
        }

        public bool isUsePool()
        {
            return this.mIsUsePool;
        }

        public void setIsUsePool(bool value)
        {
            this.mIsUsePool = value;
        }

        public void dispose()
        {
            this.onPutInPool();
        }

        public void setIsMainThreadImmeHandle(bool value)
        {
            this.mIsMainThreadImmeHandle = value;
        }

        public bool isMainThreadImmeHandle()
        {
            return this.mIsMainThreadImmeHandle;
        }
    }
}