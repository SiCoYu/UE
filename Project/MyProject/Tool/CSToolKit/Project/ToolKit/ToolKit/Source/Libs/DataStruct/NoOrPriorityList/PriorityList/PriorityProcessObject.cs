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
            
        }

        override protected void onPutInPool()
        {
            this.mPriorityObject = null;
            this.mPriority = 0.0f;
        }
    }
}