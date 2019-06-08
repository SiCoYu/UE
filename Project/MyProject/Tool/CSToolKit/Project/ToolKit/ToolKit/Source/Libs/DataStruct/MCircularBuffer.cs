namespace SDK.Lib
{
    /**
     * @brief 环形缓冲区，不支持多线程写操作
     * @brief 浪费一个自己，这样判断也好判断，并且索引也不用减 1 ，因此浪费一个字节
     * @brief 判空: mFirst == mLast
     * @brief 判满: mFirst == (mLast + 1) % len
     */
    public class MCircularBuffer : GObject
    {
        protected MDynBuffer<byte> mDynBuffer;
        protected uint mFirst;             // 当前缓冲区数据的第一个索引
        protected uint mLast;              // 当前缓冲区数据的最后一个索引的后面一个索引，浪费一个字节
        protected MByteBuffer mTmpBA;        // 临时数据

        public MCircularBuffer(uint initCapacity = BufferCV.INIT_CAPACITY, uint maxCapacity = BufferCV.MAX_CAPACITY)
        {
            this.mDynBuffer = new MDynBuffer<byte>(initCapacity, maxCapacity);

            this.mFirst = 0;
            this.mLast = 0;

            this.mTmpBA = new MByteBuffer();
        }

        public uint getFirst()
        {
            return this.mFirst;
        }

        public uint getLast()
        {
            return this.mLast;
        }

        public byte[] getBuffer()
        {
            return this.mDynBuffer.mBuffer;
        }

        public uint getSize()
        {
            return this.mDynBuffer.mSize;
        }

        public void setSize(uint value)
        {
            this.mDynBuffer.setSize(value);
        }

        public bool isLinearized()
        {
            if (this.getSize() == 0)
            {
                return true;
            }

            return this.mFirst < this.mLast;
        }

        public bool empty()
        {
            return this.mDynBuffer.mSize == 0;
        }

        public uint capacity()
        {
            return this.mDynBuffer.mCapacity;
        }

        public bool full()
        { 
            return this.capacity() == this.getSize();
        }

        // 清空缓冲区
        public void clear()
        {
            this.mDynBuffer.mSize = 0;
            this.mFirst = 0;
            this.mLast = 0;
        }

        /**
         * @brief 将数据尽量按照存储地址的从小到大排列
         */
        public void linearize()
        {
            if (this.empty())        // 没有数据
            {
                return;
            }
            if (this.isLinearized())      // 数据已经是在一块连续的内存空间
            {
                return;
            }
            else
            {
                // 数据在两个不连续的内存空间中
                char[] tmp = new char[mLast];
                MArray.Copy(this.mDynBuffer.mBuffer, 0, tmp, 0, (int)this.mLast);  // 拷贝一段内存空间中的数据到 tmp
                MArray.Copy(this.mDynBuffer.mBuffer, (int)this.mFirst, this.mDynBuffer.mBuffer, 0, (int)(this.mDynBuffer.mCapacity - this.mFirst));  // 拷贝第一段数据到 0 索引位置
                MArray.Copy(tmp, 0, this.mDynBuffer.mBuffer, (int)(this.mDynBuffer.mCapacity - this.mFirst), (int)this.mLast);      // 拷贝第二段数据到缓冲区

                this.mFirst = 0;
                this.mLast = this.getSize();
            }
        }

        /**
         * @brief 更改存储内容空间大小
         */
        protected void setCapacity(uint newCapacity) 
        {
            if (newCapacity == this.capacity())
            {
                return;
            }
            if (newCapacity < this.getSize())       // 不能分配比当前已经占有的空间还小的空间
            {
                return;
            }
            byte[] tmpbuff = new byte[newCapacity];   // 分配新的空间
            if (this.isLinearized()) // 如果是在一段内存空间
            {
                // 已经是线性空间了仍然将数据移动到索引 0 的位置
                MArray.Copy(this.mDynBuffer.mBuffer, (int)this.mFirst, tmpbuff, 0, (int)this.mDynBuffer.mSize);
            }
            else    // 如果在两端内存空间
            {
                MArray.Copy(this.mDynBuffer.mBuffer, (int)this.mFirst, tmpbuff, 0, (int)(this.mDynBuffer.mCapacity - this.mFirst));
                MArray.Copy(this.mDynBuffer.mBuffer, 0, tmpbuff, (int)(this.mDynBuffer.mCapacity - this.mFirst), (int)this.mLast);
            }

            this.mFirst = 0;
            this.mLast = mDynBuffer.mSize;
            this.mDynBuffer.mCapacity = newCapacity;
            this.mDynBuffer.mBuffer = tmpbuff;
        }

        /**
         *@brief 能否添加 num 长度的数据
         */
        protected bool canAddData(uint num)
        {
            if (this.mDynBuffer.mCapacity - this.mDynBuffer.mSize > num) // 浪费一个字节，不用 >= ，使用 > 
            {
                return true;
            }

            return false;
        }

        /**
         *@brief 向存储空尾部添加一段内容
         */
        public void pushBackArr(byte[] items, uint start, uint len)
        {
            if (!this.canAddData(len)) // 存储空间必须要比实际数据至少多 1
            {
                uint closeSize = DynBufResizePolicy.getCloseSize(len + this.mDynBuffer.mSize, this.mDynBuffer.mCapacity, this.mDynBuffer.mMaxCapacity);
                this.setCapacity(closeSize);
            }

            if (this.isLinearized())
            {
                if (len <= (this.mDynBuffer.mCapacity - this.mLast))
                {
                    MArray.Copy(items, (int)start, this.mDynBuffer.mBuffer, (int)this.mLast, (int)len);
                }
                else
                {
                    MArray.Copy(items, (int)start, this.mDynBuffer.mBuffer, (int)this.mLast, (int)(this.mDynBuffer.mCapacity - this.mLast));
                    MArray.Copy(items, (int)(this.mDynBuffer.mCapacity - this.mLast), this.mDynBuffer.mBuffer, 0, (int)(len - (this.mDynBuffer.mCapacity - this.mLast)));
                }
            }
            else
            {
                MArray.Copy(items, (int)(start), this.mDynBuffer.mBuffer, (int)this.mLast, (int)len);
            }

            this.mLast += len;
            this.mLast %= this.mDynBuffer.mCapacity;

            this.mDynBuffer.mSize += len;
        }

        public void pushBackBA(MByteBuffer bu)
        {
            //pushBack(bu.dynBuff.buffer, bu.position, bu.bytesAvailable);
            this.pushBackArr(bu.getDynBuffer().getBuffer(), 0, bu.getLength());
        }

        /**
         *@brief 向存储空头部添加一段内容
         */
        protected void pushFrontArr(byte[] items)
        {
            if (!canAddData((uint)items.Length)) // 存储空间必须要比实际数据至少多 1
            {
                uint closeSize = DynBufResizePolicy.getCloseSize((uint)items.Length + this.mDynBuffer.mSize, this.mDynBuffer.mCapacity, this.mDynBuffer.mMaxCapacity);
                this.setCapacity(closeSize);
            }

            if (this.isLinearized())
            {
                if (items.Length <= mFirst)
                {
                    MArray.Copy(items, 0, this.mDynBuffer.mBuffer, (int)(this.mFirst - items.Length), items.Length);
                }
                else
                {
                    MArray.Copy(items, (int)(items.Length - this.mFirst), this.mDynBuffer.mBuffer, 0, (int)this.mFirst);
                    MArray.Copy(items, 0, this.mDynBuffer.mBuffer, (int)(this.mDynBuffer.mCapacity - (items.Length - this.mFirst)), (int)(items.Length - this.mFirst));
                }
            }
            else
            {
                MArray.Copy(items, 0, this.mDynBuffer.mBuffer, (int)(this.mFirst - items.Length), items.Length);
            }

            if (items.Length <= mFirst)
            {
                this.mFirst -= (uint)items.Length;
            }
            else
            {
                this.mFirst = this.mDynBuffer.mCapacity - ((uint)items.Length - this.mFirst);
            }

            this.mDynBuffer.mSize += (uint)items.Length;
        }

        /**
         * @brief 从 CircularBuffer 中读取内容，并且将数据删除
         */
        public void popFrontBA(MByteBuffer byteArray, uint len)
        {
            this.frontBA(byteArray, len);
            this.popFrontLen(len);
        }

        // 仅仅是获取数据，并不删除
        public void frontBA(MByteBuffer byteArray, uint len)
        {
            byteArray.clear();          // 设置数据为初始值

            if (this.mDynBuffer.mSize >= len)          // 头部占据 4 个字节
            {
                if (this.isLinearized())      // 在一段连续的内存
                {
                    byteArray.writeBytes(this.mDynBuffer.mBuffer, this.mFirst, len);
                }
                else if (this.mDynBuffer.mCapacity - this.mFirst >= len)
                {
                    byteArray.writeBytes(this.mDynBuffer.mBuffer, this.mFirst, len);
                }
                else
                {
                    byteArray.writeBytes(this.mDynBuffer.mBuffer, this.mFirst, this.mDynBuffer.mCapacity - this.mFirst);
                    byteArray.writeBytes(this.mDynBuffer.mBuffer, 0, len - (this.mDynBuffer.mCapacity - this.mFirst));
                }
            }

            byteArray.setPos(0);        // 设置数据读取起始位置
        }

        /**
         * @brief 从 CircularBuffer 头部删除数据
         */
        public void popFrontLen(uint len)
        {
            if (this.isLinearized())  // 在一段连续的内存
            {
                this.mFirst += len;
            }
            else if (this.mDynBuffer.mCapacity - this.mFirst >= len)
            {
                this.mFirst += len;
            }
            else
            {
                this.mFirst = len - (this.mDynBuffer.mCapacity - this.mFirst);
            }

            this.mDynBuffer.mSize -= len;
        }

        // 向自己尾部添加一个 CircularBuffer
        public void pushBackCB(MCircularBuffer rhv)
        {
            if(this.mDynBuffer.mCapacity - this.mDynBuffer.mSize < rhv.getSize())
            {
                uint closeSize = DynBufResizePolicy.getCloseSize(rhv.getSize() + this.mDynBuffer.mSize, this.mDynBuffer.mCapacity, this.mDynBuffer.mMaxCapacity);
                this.setCapacity(closeSize);
            }

            //this.mSize += rhv.size;
            //this.mLast = this.mSize;

            //mTmpBA.clear();
            rhv.frontBA(this.mTmpBA, rhv.getSize());
            pushBackBA(this.mTmpBA);

            //if (rhv.isLinearized()) // 如果是在一段内存空间
            //{
            //    Array.Copy(rhv.buff, rhv.first, mBuffer, 0, rhv.size);
            //}
            //else    // 如果在两端内存空间
            //{
            //    Array.Copy(rhv.buff, rhv.first, mBuffer, 0, rhv.capacity() - rhv.first);
            //    Array.Copy(mBuffer, 0, mBuffer, rhv.capacity() - rhv.first, rhv.last);
            //}
            //rhv.clear();
        }
    }
}