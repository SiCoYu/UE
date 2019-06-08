namespace SDK.Lib
{
    /**
     * @brief 调试时候使用的相关数据信息
     */
    public class DebugSys
    {
        public UniqueNumIdGen mDebugActorUniqueId;
        public UniqueNumIdGen mDebugAuxUserDataUniqueId;
        public UniqueNumIdGen mDebugPriorityHandleUniqueId;

        public uint mTmpUniqueId;

        public DebugSys()
        {
            if(MacroDef.DEBUG_SYS)
            {
                this.mDebugActorUniqueId = new UniqueNumIdGen(0);
                this.mDebugAuxUserDataUniqueId = new UniqueNumIdGen(0);
                this.mDebugPriorityHandleUniqueId = new UniqueNumIdGen(0);
                this.mTmpUniqueId = 1000000;
            }
        }

        public void init()
        {

        }

        public void dispose()
        {

        }
    }
}