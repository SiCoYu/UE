namespace SDK.Lib
{
    public class GObject : GPoolObject, IDelayHandleItem
    {
        protected string mTypeId;     // 名字
        protected MDictionary<uint, int> mListIndexDic;       // 列表中的索引
        protected bool mIsClientDispose;       // 是否释放了资源

        public GObject()
        {
            this.mTypeId = "GObject";
            this.mListIndexDic = new MDictionary<uint, int>();       // -1 就是无效
        }

        public string getTypeId()
        {
            return this.mTypeId;
        }

        public int getListIndex(uint listUnqueId)
        {
            int listIndex = -1;

            this.mListIndexDic.tryGetValue(listUnqueId, out listIndex);

            return listIndex;
        }

        public void setListIndex(uint listUnqueId, int value)
        {
            this.mListIndexDic[listUnqueId] = value;
        }

        public bool isIndexValid(uint listUnqueId)
        {
            bool ret = false;
            int index = -1;

            if (this.mListIndexDic.tryGetValue(listUnqueId, out index))
            {
                ret = (index != -1);
            }

            return ret;
        }

        public void setInvalidListIndex(uint listUnqueId)
        {
            this.mListIndexDic.remove(listUnqueId);
        }

        public void clearAllIndex()
        {
            this.mListIndexDic.clear();
        }

        virtual public void setClientDispose(bool isDispose)
        {
            this.mIsClientDispose = isDispose;
        }

        virtual public bool isClientDispose()
        {
            return this.mIsClientDispose;
        }
    }
}