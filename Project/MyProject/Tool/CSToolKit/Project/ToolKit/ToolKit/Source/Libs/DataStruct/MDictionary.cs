using System.Collections.Generic;

namespace SDK.Lib
{
    //public class MDictionary<TKey, TValue> where TValue : IComparer<TValue>
    //public class MDictionary<TKey, TValue> where TValue : class
    public class MDictionary<TKey, TValue> : GContainerObject
    {
        protected Dictionary<TKey, TValue> mData;

        public MDictionary()
        {
            this.mData = new Dictionary<TKey, TValue>();
        }

        public Dictionary<TKey, TValue> getData()
        {
            return this.mData;
        }

        public void init()
        {

        }

        public void dispose()
        {
            this.clear();
            this.mData = null;
        }

        public int getCount()
        {
            return this.mData.Count;
        }

        public TValue this[TKey key]
        {
            get
            {
                return this.value(key);
            }
            set
            {
                this.add(key, value);
            }
        }

        public TValue value(TKey key)
        {
            if (this.mData.ContainsKey(key))
            {
                return this.mData[key];
            }

            return default(TValue);
        }

        public TKey key(TValue value)
        {
            foreach (KeyValuePair<TKey, TValue> kv in this.mData)
            {
                if (kv.Value.Equals(value))
                //if (kv.Value == value)
                {
                    return kv.Key;
                }
            }
            return default(TKey);
        }

        public Dictionary<TKey, TValue>.KeyCollection keys
        {
            get
            {
                return this.mData.Keys;
            }
        }

        public Dictionary<TKey, TValue>.ValueCollection values
        {
            get
            {
                return this.mData.Values;
            }
        }

        public int count()
        {
            return this.mData.Keys.Count;
        }

        public Dictionary<TKey, TValue>.Enumerator getEnumerator()
        {
            return this.mData.GetEnumerator();
        }

        public void add(TKey key, TValue value)
        {
            this.mData[key] = value;
        }

        public void remove(TKey key)
        {
            this.mData.Remove(key);
        }

        public TValue getAndRemoveByKey(TKey key)
        {
            TValue value = this.value(key);
            this.remove(key);
            return value;
        }

        public void clear()
        {
            this.mData.Clear();
        }

        public bool tryGetValue(TKey key, out TValue value)
        {
            return this.mData.TryGetValue(key, out value);
        }

        public bool containsKey(TKey key)
        {
            return this.mData.ContainsKey(key);
        }

        public bool containsValue(TValue value)
        {
            foreach (KeyValuePair<TKey, TValue> kv in this.mData)
            {
                if (kv.Value.Equals(value))
                //if (kv.Value == value)
                {
                    return true;
                }
            }
        
            return false;
        }

        public TValue at(int idx)
        {
            int curidx = 0;
            TValue ret = default(TValue);

            foreach (KeyValuePair<TKey, TValue> kvp in this.mData)
            {
                if(curidx == idx)
                {
                    ret = kvp.Value;
                    break;
                }
            }

            return ret;
        }
    }
}