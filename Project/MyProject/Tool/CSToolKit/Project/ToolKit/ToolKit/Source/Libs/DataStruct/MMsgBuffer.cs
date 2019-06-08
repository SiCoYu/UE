namespace SDK.Lib
{
    public class MMsgBuffer : GObject
    {
        protected MCircularBuffer mCircularBuffer;  // 环形缓冲区

        protected MByteBuffer mHeaderBA;            // 主要是用来分析头的大小
        protected MByteBuffer mMsgBodyBA;           // 返回的字节数组

        public MMsgBuffer(uint initCapacity = BufferCV.INIT_CAPACITY, uint maxCapacity = BufferCV.MAX_CAPACITY)
        {
            this.mCircularBuffer = new MCircularBuffer(initCapacity, maxCapacity);
            this.mHeaderBA = new MByteBuffer();
            this.mMsgBodyBA = new MByteBuffer();
        }

        public MByteBuffer getHeaderBA()
        {
            return this.mHeaderBA;
        }

        public MByteBuffer getMsgBodyBA()
        {
            return this.mMsgBodyBA;
        }

        public MCircularBuffer getCircularBuffer()
        {
            return this.mCircularBuffer;
        }

        // 设置网络字节序
        public void setEndian(MEndian end)
        {
            this.mHeaderBA.setEndian(end);
            this.mMsgBodyBA.setEndian(end);
        }

        /**
         * @brief 检查 CB 中是否有一个完整的消息
         */
        protected bool checkHasMsg()
        {
            this.mCircularBuffer.frontBA(this.mHeaderBA, MsgCV.HEADER_SIZE);  // 将数据读取到 mHeaderBA
            uint msglen = 0;
            this.mHeaderBA.readUnsignedInt32(ref msglen);

            if (MacroDef.MSG_COMPRESS)
            {
                if ((msglen & MsgCV.PACKET_ZIP) > 0)         // 如果有压缩标志
                {
                    msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
                }
            }
            if (msglen <= this.mCircularBuffer.getSize() - MsgCV.HEADER_SIZE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief 获取前面的第一个完整的消息数据块
         */
        public bool popFront()
        {
            bool ret = false;

            // 至少要是 DataCV.HEADER_SIZE 大小加 1 ，如果正好是 DataCV.HEADER_SIZE ，那只能说是只有大小字段，没有内容
            if (this.mCircularBuffer.getSize() > MsgCV.HEADER_SIZE)
            {
                // 如果不够整个消息的长度，还是不能去掉消息头的
                this.mCircularBuffer.frontBA(this.mHeaderBA, MsgCV.HEADER_SIZE);
                uint msglen = 0;
                this.mHeaderBA.readUnsignedInt32(ref msglen);

                if (MacroDef.MSG_COMPRESS)
                {
                    if ((msglen & MsgCV.PACKET_ZIP) > 0)         // 如果有压缩标志
                    {
                        msglen &= (~MsgCV.PACKET_ZIP);         // 去掉压缩标志位
                    }
                }

                if (msglen <= this.mCircularBuffer.getSize() - MsgCV.HEADER_SIZE)
                {
                    this.mCircularBuffer.popFrontLen(MsgCV.HEADER_SIZE);
                    this.mCircularBuffer.popFrontBA(this.mMsgBodyBA, msglen);

                    ret = true;
                }
            }

            if (this.mCircularBuffer.empty())     // 如果已经清空，就直接重置
            {
                this.mCircularBuffer.clear();    // 读写指针从头开始，方式写入需要写入两部分
            }

            return ret;
        }

        /**
         * @brief KBEngine 引擎消息处理
         */
        public bool popFrontAll()
        {
            bool ret = false;

            if (!this.mCircularBuffer.empty())
            {
                ret = true;
                this.mCircularBuffer.linearize();
                this.mCircularBuffer.popFrontBA(this.mMsgBodyBA, this.mCircularBuffer.getSize());
                this.mCircularBuffer.clear();
            }

            return ret;
        }
    }
}