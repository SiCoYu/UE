namespace SDK.Lib
{
    /**
     * @brief 线程安全列表， T 是 Object ，便于使用 Equal 比较地址
     */
    public class MLockList<T> : GObject
    {
        protected MDynBuffer<T> mDynamicBuffer;
        protected MMutex mVisitMutex;
        protected T mRetItem;

        public MLockList(string name, uint initCapacity = 32/*DataCV.INIT_ELEM_CAPACITY*/, uint maxCapacity = 8 * 1024 * 1024/*DataCV.MAX_CAPACITY*/)
        {
            this.mDynamicBuffer = new MDynBuffer<T>(initCapacity, maxCapacity);
            this.mVisitMutex = new MMutex(false, name);
        }

        //public uint Count
        //{ 
        //    get
        //    {
        //        using (MLock mlock = new MLock(mVisitMutex))
        //        {
        //            return mDynamicBuffer.mSize;
        //        }
        //    }
        //}

        public uint count()
        {
            using (MLock mlock = new MLock(mVisitMutex))
            {
                return this.mDynamicBuffer.mSize;
            }
        }

        public T this[int index] 
        { 
            get
            {
                using (MLock mlock = new MLock(mVisitMutex))
                {
                    if (index < mDynamicBuffer.mSize)
                    {
                        return this.mDynamicBuffer.mBuffer[index];
                    }
                    else
                    {
                        return default(T);
                    }
                }
            }

            set
            {
                using (MLock mlock = new MLock(mVisitMutex))
                {
                    this.mDynamicBuffer.mBuffer[index] = value;
                }
            }
        }

        public void add(T item)
        {
            using (MLock mlock = new MLock(mVisitMutex))
            {
                if (this.mDynamicBuffer.mSize >= mDynamicBuffer.mCapacity)
                {
                    this.mDynamicBuffer.extendDeltaCapicity(1);
                }

                this.mDynamicBuffer.mBuffer[mDynamicBuffer.mSize] = item;
                ++this.mDynamicBuffer.mSize;
            }
        }

        public bool remove(T item)
        {
            using (MLock mlock = new MLock(mVisitMutex))
            {
                int idx = 0;
                foreach (var elem in this.mDynamicBuffer.mBuffer)
                {
                    if(item.Equals(elem))       // 地址比较
                    {
                        this.removeAt(idx);
                        return true;
                    }

                    ++idx;
                }

                return false;
            }
        }

        public T removeAt(int index)
        {
            using (MLock mlock = new MLock(mVisitMutex))
            {
                if (index < this.mDynamicBuffer.mSize)
                {
                    this.mRetItem = this.mDynamicBuffer.mBuffer[index];

                    if (index < this.mDynamicBuffer.mSize)
                    {
                        if (index != this.mDynamicBuffer.mSize - 1 && 1 != this.mDynamicBuffer.mSize) // 如果删除不是最后一个元素或者总共就大于一个元素
                        {
                            MArray.Copy(this.mDynamicBuffer.mBuffer, index + 1, this.mDynamicBuffer.mBuffer, index, (int)(this.mDynamicBuffer.mSize - 1 - index));
                        }

                        --this.mDynamicBuffer.mSize;
                    }
                }
                else
                {
                    this.mRetItem = default(T);
                }

                return this.mRetItem;
            }
        }

        public int indexOf(T item)
        {
            using (MLock mlock = new MLock(mVisitMutex))
            {
                int idx = 0;

                foreach (var elem in this.mDynamicBuffer.mBuffer)
                {
                    if (item.Equals(elem))       // 地址比较
                    {
                        this.removeAt(idx);
                        return idx;
                    }

                    ++idx;
                }

                return -1;
            }
        }
    }
}