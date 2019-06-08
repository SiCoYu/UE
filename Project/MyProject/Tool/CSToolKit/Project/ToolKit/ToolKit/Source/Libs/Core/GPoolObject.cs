namespace SDK.Lib
{
    /*
     * @brief 基本缓冲对象
     */
    public class GPoolObject : GObjectBase
    {
        protected bool mIsUsePool;      // 是否使用 Pool
        protected int mNumUniqueId;
        protected string mStrUniqueId;

        public GPoolObject()
        {
            this.mIsUsePool = false;
            this.onGetFromPool();
        }

        virtual public void init()
        {
            this.onInit();
        }

        virtual protected void onInit()
        {

        }

        virtual protected void onGetFromPool()
        {

        }

        virtual protected void onPutInPool()
        {

        }

        virtual public void dispose()
        {
            this.onPutInPool();
            this.onDestroy();
        }

        virtual public void destroy()
        {
            this.onDestroy();
        }

        virtual protected void onDestroy()
        {

        }

        public bool isUsePool()
        {
            return this.mIsUsePool;
        }

        public void setIsUsePool(bool value)
        {
            this.mIsUsePool = value;
        }

        public void putInPool()
        {
            this.onPutInPool();
        }

        public void getFromPool()
        {
            this.onGetFromPool();
        }

        public void setNumUniqueId(int value)
        {
            this.mNumUniqueId = value;
        }

        public int getNumUniqueId()
        {
            return this.mNumUniqueId;
        }

        public void setStrUniqueId(string value)
        {
            this.mStrUniqueId = value;
        }

        public string getStrUniqueId()
        {
            return this.mStrUniqueId;
        }
    }
}