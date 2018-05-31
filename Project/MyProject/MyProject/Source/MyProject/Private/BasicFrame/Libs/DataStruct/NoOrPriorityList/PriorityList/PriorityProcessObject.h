namespace SDK.Lib
{
    /**
     * @brief 优先级队列对象
     */
    public class PriorityProcessObject : GObject
    {
        public INoOrPriorityObject mPriorityObject;
        public float mPriority;

        public PriorityProcessObject()
        {
            this.onPutInPool();
        }

        public void putInPool()
        {
            this.onPutInPool();
        }

        public void getFromPool()
        {
            this.onGetFromPool();
        }

        public void dispose()
        {
            this.onPutInPool();
        }

        public void setIsUsePool(bool value)
        {
            this.mIsUsePool = value;
        }

        public bool isUsePool()
        {
            return this.mIsUsePool;
        }

        public void onPutInPool()
        {
            this.mPriorityObject = null;
            this.mPriority = 0.0f;
        }

        public void onGetFromPool()
        {

        }

        public int getBufferType()
        {
            return (int)BufferType.eBT_PriorityProcessObject;
        }
    }
}