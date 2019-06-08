using System;
using System.Collections.Generic;

namespace SDK.Lib
{
    /**
     * @brief 对系统 List 的封装
     */
    public class MList<T> : GContainerObject
    {
        //public delegate int CompareFunc(T left, T right);

        protected List<T> mData;
        protected int mUniqueId;       // 唯一 Id ，调试使用
        protected int mEleTotal;       // 元素总数

        protected Dictionary<T, int> mDic;    // 为了加快查找速度，当前 Element 到索引映射，GObject 使用自己保存索引， int 基本类型保存在这里面
        protected bool mIsSpeedUpFind;  // 是否加快查询，这个只适用于元素在列表中是唯一的，例如引用之类的，如果有相同的，就会有问题，注意了
        protected bool mIsOpKeepSort;           // 操作的时候是否保持排序
        protected uint mListGlobalUniqueId;

        protected static UniqueNumIdGen mUniqueNumIdGen = new UniqueNumIdGen(0);

        public MList()
        {
            this._baseInit();

            //if(this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public MList(int capacity)
        {
            this.mData = new List<T>(capacity);
            this.mEleTotal = capacity;

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public MList(T[] array)
        {
            this._baseInit();

            int index = 0;
            int arrayLen = array.Length;

            while(index < arrayLen)
            {
                this.add(array[index]);

                index += 1;
            }
        }

        protected void _baseInit()
        {
            this.mEleTotal = 0;
            this.mData = new List<T>();
            this.mIsSpeedUpFind = false;
            this.mIsOpKeepSort = false;
            this.mListGlobalUniqueId = mUniqueNumIdGen.genNewId();
        }

        public void init()
        {
            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void dispose()
        {
            this.clear();

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}

            this.mData = null;
            this.mDic = null;
        }

        public void setIsSpeedUpFind(bool value)
        {
            this.mIsSpeedUpFind = value;

            if(this.mIsSpeedUpFind)
            {
                this.mDic = new Dictionary<T, int>();
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void setIsOpKeepSort(bool value)
        {
            this.mIsOpKeepSort = value;

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public T[] ToArray()
        {
            return this.mData.ToArray();
        }

        public List<T> list()
        {
            return this.mData;
        }

        public int getUniqueId()
        {
            return this.mUniqueId;
        }

        public void setUniqueId(int value)
        {
            this.mUniqueId = value;
        }

        // 检查索引是否无效
        protected bool checkIndexInvalid()
        {
            bool ret = false;

            // 如果大小不想等
            if(this.mEleTotal != this.mData.Count)
            {
                ret = true;
            }

            int index = 0;

            // 如果有的值已经是空值
            while(index < this.mEleTotal)
            {
                if(null == this.mData[index])
                {
                    ret = true;
                }

                index += 1;
            }

            return ret;
        }

        // 索引无效回调处理
        protected void _onIndexInvalidHandle()
        {
            Console.Write("MList error" + " \n");
        }

        // 如果使用 mIsSpeedUpFind，在加入列表的之前，一定不能在其它列表
        public void add(T item)
        {
            this.mData.Add(item);
            this.mEleTotal += 1;

            if (this.mIsSpeedUpFind)
            {
                if (item is GObject)
                {
                    (item as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 1);
                }
                else
                {
                    this.mDic[item] = this.count() - 1;   
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        // 主要是 Add 一个 float 类型的 Vector3
        public void add(T item_1, T item_2, T item_3)
        {
            this.mData.Add(item_1);
            this.mEleTotal += 1;
            this.mData.Add(item_2);
            this.mEleTotal += 1;
            this.mData.Add(item_3);
            this.mEleTotal += 1;

            if (this.mIsSpeedUpFind)
            {
                if(item_1 is GObject)
                {
                    (item_1 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 3);
                }
                else
                {
                    this.mDic[item_1] = this.count() - 3;
                }

                if(item_2 is GObject)
                {
                    (item_2 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 2);
                }
                else
                {
                    this.mDic[item_2] = this.count() - 2;
                }

                if (item_3 is GObject)
                {
                    (item_3 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 1);
                }
                else
                {
                    this.mDic[item_3] = this.count() - 1;
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        // 主要是 Add 一个 float 类型的 UV
        public void add(T item_1, T item_2)
        {
            this.mData.Add(item_1);
            this.mEleTotal += 1;
            this.mData.Add(item_2);
            this.mEleTotal += 1;

            if (this.mIsSpeedUpFind)
            {
                if(item_1 is GObject)
                {
                    (item_1 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 2);
                }
                else
                {
                    this.mDic[item_1] = this.count() - 2;
                }

                if(item_2 is GObject)
                {
                    (item_2 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 1);
                }
                else
                {
                    this.mDic[item_2] = this.count() - 1;
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        // 主要是 Add 一个 byte 类型的 Color32
        public void add(T item_1, T item_2, T item_3, T item_4)
        {
            this.mData.Add(item_1);
            this.mEleTotal += 1;
            this.mData.Add(item_2);
            this.mEleTotal += 1;
            this.mData.Add(item_3);
            this.mEleTotal += 1;
            this.mData.Add(item_4);
            this.mEleTotal += 1;

            if (this.mIsSpeedUpFind)
            {
                if(item_1 is GObject)
                {
                    (item_1 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 4);
                }
                else
                {
                    this.mDic[item_1] = this.count() - 4;
                }

                if (item_2 is GObject)
                {
                    (item_2 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 3);
                }
                else
                {
                    this.mDic[item_2] = this.count() - 3;
                }

                if(item_3 is GObject)
                {
                    (item_3 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 2);
                }
                else
                {
                    this.mDic[item_3] = this.count() - 2;
                }

                if(item_4 is GObject)
                {
                    (item_4 as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 1);
                }
                else
                {
                    this.mDic[item_4] = this.count() - 1;
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void push(T item)
        {
            this.mData.Add(item);
            this.mEleTotal += 1;

            if (this.mIsSpeedUpFind)
            {
                if(item is GObject)
                {
                    (item as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 1);
                }
                else
                {
                    this.mDic[item] = this.count() - 1;
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public bool remove(T item)
        {
            if (this.mIsSpeedUpFind)
            {
                return this.effectiveRemove(item);
            }
            else
            {
                bool ret = this.mData.Remove(item);

                if(ret)
                {
                    this.mEleTotal -= 1;
                }

                return ret;
            }
        }

        public T this[int index]
        {
            get
            {
                return this.mData[index];
            }
            set
            {
                if (this.mIsSpeedUpFind)
                {
                    if(value is GObject)
                    {
                        (value as GObject).setListIndex(this.mListGlobalUniqueId, index);
                    }
                    else
                    {
                        this.mDic[value] = index;
                    }
                }

                this.mData[index] = value;

                //if (this.checkIndexInvalid())
                //{
                //    this.OnIndexInvalidHandle();
                //}
            }
        }

        public T get(int index)
        {
            return this.mData[index];
        }

        public void set(int index, T value)
        {
            this.mData[index] = value;
        }

        public T getAndRemoveByIndex(int index)
        {
            T ret;

            ret = this.get(index);
            this.removeAt(index);

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}

            return ret;
        }

        public void clear()
        {
            this.mData.Clear();
            this.mEleTotal = 0;

            if (this.mIsSpeedUpFind)
            {
                this.mDic.Clear();
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public int count()
        {
            //return this.mData.Count;
            return this.mEleTotal;
        }

        public void setLength(int value)
        {
            this.mData.Capacity = value;

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void removeAt(int index)
        {
            if (this.mIsSpeedUpFind)
            {
                this.effectiveRemove(this.mData[index]);
            }
            else
            {
                if (index < this.count())
                {
                    this.mData.RemoveAt(index);
                    this.mEleTotal -= 1;
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public int indexOf(T item)
        {
            if (this.mIsSpeedUpFind)
            {
                bool hasItem = false;
                int retIndex = -1;

                if(item is GObject)
                {
                    hasItem = (item as GObject).isIndexValid(this.mListGlobalUniqueId);
                    retIndex = (item as GObject).getListIndex(this.mListGlobalUniqueId);
                }
                else
                {
                    hasItem = this.mDic.ContainsKey(item);
                    retIndex = this.mDic[item];
                }
                
                if(hasItem)
                {
                    return retIndex;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return this.mData.IndexOf(item);
            }
        }

        public void insert(int index, T item)
        {
            if (index <= this.count())
            {
                this.mData.Insert(index, item);
                this.mEleTotal += 1;

                if(this.mIsSpeedUpFind)
                {
                    if(item is GObject)
                    {
                        (item as GObject).setListIndex(this.mListGlobalUniqueId, index);
                    }
                    else
                    {
                        this.mDic[item] = index;
                    }

                    this.updateIndex(index + 1);
                }
            }
            else
            {

            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public bool contains(T item)
        {
            if(this.mIsSpeedUpFind)
            {
                if(item is GObject)
                {
                    return (item as GObject).isIndexValid(this.mListGlobalUniqueId);
                }
                else
                {
                    return this.mDic.ContainsKey(item);
                }
            }
            else
            {
                return this.mData.Contains(item);
            }
        }

        public void sort(System.Comparison<T> comparer)
        {
            this.mData.Sort(comparer);

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void merge(MList<T> appendList)
        {
            if(appendList != null)
            {
                foreach(T item in appendList.list())
                {
                    this.mData.Add(item);
                    this.mEleTotal += 1;

                    if (this.mIsSpeedUpFind)
                    {
                        if(item is GObject)
                        {
                            (item as GObject).setListIndex(this.mListGlobalUniqueId, this.count() - 1);
                        }
                        else
                        {
                            this.mDic[item] = this.count() - 1;
                        }
                    }
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void addRange(MList<T> collection)
        {
            this.mData.AddRange(collection.list());
        }

        // 快速移除元素
        protected bool effectiveRemove(T item)
        {
            bool ret = false;
            bool hasItem = false;

            if(item is GObject)
            {
                hasItem = (item as GObject).isIndexValid(this.mListGlobalUniqueId);
            }
            else
            {
                hasItem = this.mDic.ContainsKey(item);
            }

            if(hasItem)
            {
                ret = true;
                int idx = -1;

                if(item is GObject)
                {
                    idx = (item as GObject).getListIndex(this.mListGlobalUniqueId);
                    (item as GObject).setInvalidListIndex(this.mListGlobalUniqueId);
                }
                else
                {
                    idx = this.mDic[item];
                    this.mDic.Remove(item);
                }

                if(idx == this.count() - 1)    // 如果是最后一个元素，直接移除
                {
                    this.mData.RemoveAt(idx);
                    this.mEleTotal -= 1;
                }
                else
                {
                    if(!this.mIsOpKeepSort)
                    {
                        this.mData[idx] = this.mData[this.count() - 1];
                        this.mData.RemoveAt(this.count() - 1);
                        if(this.mData[idx] is GObject)
                        {
                            (this.mData[idx] as GObject).setListIndex(this.mListGlobalUniqueId, idx);
                        }
                        else
                        {
                            this.mDic[this.mData[idx]] = idx;
                        }
                        this.mEleTotal -= 1;
                    }
                    else
                    {
                        this.mData.RemoveAt(idx);
                        this.mEleTotal -= 1;
                        this.updateIndex(idx);
                    }
                }
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}

            return ret;
        }

        protected void updateIndex(int idx)
        {
            int len = this.count();

            while (idx < len)
            {
                if (this.mData[idx] is GObject)
                {
                    (this.mData[idx] as GObject).setListIndex(this.mListGlobalUniqueId, idx);
                }
                else
                {
                    this.mDic[this.mData[idx]] = idx;
                }

                ++idx;
            }

            //if (this.checkIndexInvalid())
            //{
            //    this.OnIndexInvalidHandle();
            //}
        }

        public void appendList(MList<T> appendList)
        {
            int index = 0;
            int listLen = appendList.count();

            while(index < listLen)
            {
                this.add(appendList.get(index));
                index += 1;
            }
        }
    }
}