namespace SDK.Lib
{
    public class MsgRouteNotify
    {
        protected MList<MsgRouteDispatchHandle> mDispatchList;

        public MsgRouteNotify()
        {
            this.mDispatchList = new MList<MsgRouteDispatchHandle>();
        }

        public void addOneNotify(MsgRouteDispatchHandle disp)
        {
            if(!this.mDispatchList.contains(disp))
            {
                this.mDispatchList.add(disp);
            }
        }

        public void removeOneNotify(MsgRouteDispatchHandle disp)
        {
            if(this.mDispatchList.contains(disp))
            {
                this.mDispatchList.remove(disp);
            }
        }

        public void handleMsg(MsgRouteBase msg)
        {
            int index = 0;
            int liseLen = this.mDispatchList.count();

            while(index < liseLen)
            {
                this.mDispatchList[index].handleMsg(msg);

                ++index;
            }

            // 暂时不用缓存，非资源数据结构重新申请内存应该不会太耗时
            //Ctx.msInstance.mPoolSys.deleteObj(msg);
        }
    }
}