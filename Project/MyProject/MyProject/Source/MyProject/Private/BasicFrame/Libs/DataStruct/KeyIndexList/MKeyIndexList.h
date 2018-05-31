namespace SDK.Lib
{
    /**
     * @brief 通过 Key 索引的列表
     */
    public class MKeyIndexList<TKey, TValue> where TValue : class
    {
        protected MList<TValue> mList;              // 数据列表
        protected MDictionary<TKey, TValue> mIndexDic;   // Key 字典

        public MKeyIndexList()
        {
            this.mList = new MList<TValue>();
            this.mList.setIsSpeedUpFind(true);
            this.mList.setIsOpKeepSort(true);

            this.mIndexDic = new MDictionary<TKey, TValue>();
        }

        public void clear()
        {
            this.mList.clear();
            this.mIndexDic.clear();
        }

        public MList<TValue> getList()
        {
            return this.mList;
        }

        public TValue get(int index)
        {
            return this.mList.get(index);
        }

        public MDictionary<TKey, TValue> getIndexDic()
        {
            return this.mIndexDic;
        }

        public void add(TKey key, TValue value)
        {
            if(!this.mIndexDic.containsKey(key))
            {
                this.mList.add(value);
                this.mIndexDic.add(key, value);
            }
        }

        public void addToFirst(TKey key, TValue value)
        {
            this.mList.insert(0, value);
            this.mIndexDic.add(key, value);
        }

        public void addToSecond(TKey key, TValue value)
        {
            this.mList.insert(1, value);
            this.mIndexDic.add(key, value);
        }

        public void remove(TKey key)
        {
            if(this.mIndexDic.containsKey(key))
            {
                this.mList.remove(this.mIndexDic.value(key));
                this.mIndexDic.remove(key);
            }
        }

        public TValue getAndRemoveByKey(TKey key)
        {
            TValue item = this.value(key);
            this.remove(key);
            return item;
        }

        public TValue value(TKey key)
        {
            TValue ret = null;

            if(this.mIndexDic.containsKey(key))
            {
                ret = this.mIndexDic.value(key);
            }

            return ret;
        }

        public int count()
        {
            return this.mList.count();
        }

        public bool containsKey(TKey key)
        {
            return this.mIndexDic.containsKey(key);
        }
    }
}