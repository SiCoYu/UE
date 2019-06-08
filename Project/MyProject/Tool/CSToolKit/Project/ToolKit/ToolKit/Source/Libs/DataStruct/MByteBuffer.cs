using System.Text;

namespace SDK.Lib
{
    /**
     *@brief MByteBuffer 功能
     */
    public class MByteBuffer : GObject, IDispatchObject
    {
        // 读写临时缓存，这个如果是单线程其实可以共享的
        public byte[] mWriteFloatBytes = null;
        public byte[] mWriteDoubleBytes = null;
        
        public byte[] mReadFloatBytes = null;
        public byte[] mReadDoubleBytes = null;

        protected MDynBuffer<byte> mDynBuffer;
        protected uint mPos;          // 当前可以读取的位置索引
        protected MEndian mEndian;          // 大端小端

        protected byte[] mPadBytes;

        public MByteBuffer(uint initCapacity = BufferCV.INIT_CAPACITY, uint maxCapacity = BufferCV.MAX_CAPACITY, MEndian endian = MEndian.eLITTLE_ENDIAN)
        {
            this.mEndian = endian;        // 缓冲区默认是小端的数据，因为服务器是 linux 的
            this.mDynBuffer = new MDynBuffer<byte>(initCapacity, maxCapacity);

            this.mReadFloatBytes = new byte[sizeof(float)];
            this.mReadDoubleBytes = new byte[sizeof(double)];
        }

        public MDynBuffer<byte> getDynBuffer()
        {
            return this.mDynBuffer;
        }

		public uint getBytesAvailable()
        {
            return (this.mDynBuffer.getSize() - this.mPos);
        }

		public MEndian getEndian()
        {
            return this.mEndian;
        }

        public void setEndian(MEndian end)
        {
            this.mEndian = end;
        }

		public uint getLength()
        {
            return this.mDynBuffer.getSize();
        }

        public void setLength(uint value)
        {
            this.mDynBuffer.setSize(value);
        }

        public void setPos(uint pos)
        {
            this.mPos = pos;
        }

        public uint getPos()
        {
            return this.mPos;
        }

        public void clear ()
        {
            this.mPos = 0;
            this.mDynBuffer.setSize(0);
        }

        // 检查是否有足够的大小可以扩展
        protected bool canWrite(uint delta)
        {
            if(this.mDynBuffer.getSize() + delta > this.mDynBuffer.getCapacity())
            {
                return false;
            }

            return true;
        }

        // 读取检查
        protected bool canRead(uint delta)
        {
            if (this.mPos + delta > this.mDynBuffer.getSize())
            {
                return false;
            }

            return true;
        }

        protected void extendDeltaCapicity(uint delta)
        {
            this.mDynBuffer.extendDeltaCapicity(delta);
        }

        protected void advPos(uint num)
        {
            this.mPos += num;
        }

        protected void advPosAndLen(uint num)
        {
            this.mPos += num;
            this.setLength(this.mPos);
        }

        public void incPosDelta(int delta)        // 添加 pos delta 数量
        {
            this.mPos += (uint)delta;
        }

        public void decPosDelta(int delta)     // 减少 pos delta 数量
        {
            this.mPos -= (uint)delta;
        }

        public MByteBuffer readInt8(ref byte tmpByte)
        {
            if (this.canRead(sizeof(char)))
            {
                tmpByte = this.mDynBuffer.getBuffer()[(int)this.mPos];
                this.advPos(sizeof(char));
            }

            return this;
        }

        public MByteBuffer readUnsignedInt8(ref byte tmpByte)
        {
            if (this.canRead(sizeof(byte)))
            {
                tmpByte = mDynBuffer.getBuffer()[(int)this.mPos];
                this.advPos(sizeof(byte));
            }

            return this;
        }

        public MByteBuffer readInt16(ref short tmpShort)
        {
            if (this.canRead(sizeof(short)))
            {
                tmpShort = MBitConverter.ToInt16(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

                this.advPos(sizeof(short));
            }

            return this;
        }

        public MByteBuffer readUnsignedInt16(ref ushort tmpUshort)
        {
            if (this.canRead(sizeof(ushort)))
            {
                tmpUshort = MBitConverter.ToUInt16(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

                this.advPos(sizeof(ushort));
            }

            return this;
        }

        public MByteBuffer readInt32(ref int tmpInt)
        {
            if (this.canRead(sizeof(int)))
            {
                tmpInt = MBitConverter.ToInt32(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

                this.advPos(sizeof(int));
            }

            return this;
        }

        public MByteBuffer readUnsignedInt32(ref uint tmpUint)
        {
            if (this.canRead(sizeof(uint)))
            {
                // 如果字节序和本地字节序不同，需要转换
                tmpUint = MBitConverter.ToUInt32(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

                this.advPos(sizeof(uint));
            }

            return this;
        }

        public MByteBuffer readInt64(ref long tmpLong)
        {
            if (this.canRead(sizeof(long)))
            {
                tmpLong = MBitConverter.ToInt64(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

                this.advPos(sizeof(long));
            }

            return this;
        }

        public MByteBuffer readUnsignedInt64(ref ulong tmpUlong)
        {
            if (this.canRead(sizeof(ulong)))
            {
                tmpUlong = MBitConverter.ToUInt64(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

                this.advPos(sizeof(ulong));
            }

            return this;
        }

        public MByteBuffer readFloat(ref float tmpFloat)
        {
            if (this.canRead(sizeof(float)))
            {
                if (this.mEndian != SystemEndian.msLocalEndian)
                {
                    MArray.Copy(mDynBuffer.getBuffer(), (int)this.mPos, this.mReadFloatBytes, 0, sizeof(float));
                    MArray.Reverse(this.mReadFloatBytes, 0, sizeof(float));
                    tmpFloat = System.BitConverter.ToSingle(this.mReadFloatBytes, (int)this.mPos);
                }
                else
                {
                    tmpFloat = System.BitConverter.ToSingle(this.mDynBuffer.getBuffer(), (int)this.mPos);
                }

                this.advPos(sizeof(float));
            }

            return this;
        }

        public MByteBuffer readDouble(ref double tmpDouble)
        {
            if (this.canRead(sizeof(double)))
            {
                if (this.mEndian != SystemEndian.msLocalEndian)
                {
                    MArray.Copy(this.mDynBuffer.getBuffer(), (int)this.mPos, this.mReadDoubleBytes, 0, sizeof(double));
                    MArray.Reverse(this.mReadDoubleBytes, 0, sizeof(double));
                    tmpDouble = System.BitConverter.ToDouble(this.mReadDoubleBytes, (int)this.mPos);
                }
                else
                {
                    tmpDouble = System.BitConverter.ToDouble(this.mDynBuffer.getBuffer(), (int)this.mPos);
                }

                this.advPos(sizeof(double));
            }

            return this;
        }

        //public MByteBuffer readMultiByte(ref string tmpStr, uint len, Encoding charSet)
        public MByteBuffer readMultiByte(ref string tmpStr, uint len, MEncode gkCharSet)
        {
            Encoding charSet = UtilSysLibWrap.convOneEncode2AnotherEncode(gkCharSet);

            // 如果是 unicode ，需要大小端判断
            if(this.canRead(len))
            {
                tmpStr = charSet.GetString(this.mDynBuffer.getBuffer(), (int)this.mPos, (int)len);
                this.advPos(len);
            }

            return this;
        }

        // 这个是字节读取，没有大小端的区别
        public MByteBuffer readBytes(ref byte[] tmpBytes, uint len)
        {
            if (this.canRead(len))
            {
                MArray.Copy(this.mDynBuffer.getBuffer(), (int)this.mPos, tmpBytes, 0, (int)len);
                this.advPos(len);
            }

            return this;
        }

        // 如果要使用 writeInt8 ，直接使用 writeMultiByte 这个函数
        public void writeInt8(char value)
        {
            if (!this.canWrite(sizeof(char)))
            {
                this.extendDeltaCapicity(sizeof(char));
            }

            this.mDynBuffer.getBuffer()[this.mPos] = (byte)value;
            this.advPosAndLen(sizeof(char));
        }

        public void writeUnsignedInt8(byte value)
        {
            if (!this.canWrite(sizeof(byte)))
            {
                this.extendDeltaCapicity(sizeof(byte));
            }

            this.mDynBuffer.getBuffer()[this.mPos] = value;
            this.advPosAndLen(sizeof(byte));
        }

        public void writeInt16 (short value)
        {
            if (!this.canWrite(sizeof(short)))
            {
                this.extendDeltaCapicity(sizeof(short));
            }
            
            MBitConverter.GetBytes(value, this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

            this.advPosAndLen(sizeof(short));
        }

        public void writeUnsignedInt16(ushort value)
        {
            if (!this.canWrite(sizeof(ushort)))
            {
                this.extendDeltaCapicity(sizeof(ushort));
            }

            MBitConverter.GetBytes(value, this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

            this.advPosAndLen(sizeof(ushort));
        }

        public void writeInt32(int value)
        {
            if (!this.canWrite(sizeof(int)))
            {
                this.extendDeltaCapicity(sizeof(int));
            }

            MBitConverter.GetBytes(value, this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

            this.advPosAndLen(sizeof(int));
        }

		public void writeUnsignedInt32 (uint value, bool bchangeLen = true)
        {
            if (!this.canWrite(sizeof(uint)))
            {
                this.extendDeltaCapicity(sizeof(uint));
            }

            MBitConverter.GetBytes(value, this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

            if (bchangeLen)
            {
                this.advPosAndLen(sizeof(uint));
            }
            else
            {
                this.advPos(sizeof(uint));
            }
        }

        public void writeInt64(long value)
        {
            if (!this.canWrite(sizeof(long)))
            {
                this.extendDeltaCapicity(sizeof(long));
            }

            MBitConverter.GetBytes(value, this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

            this.advPosAndLen(sizeof(long));
        }

        public void writeUnsignedInt64(ulong value)
        {
            if (!this.canWrite(sizeof(ulong)))
            {
                this.extendDeltaCapicity(sizeof(ulong));
            }

            MBitConverter.GetBytes(value, this.mDynBuffer.getBuffer(), (int)this.mPos, this.mEndian);

            this.advPosAndLen(sizeof(ulong));
        }

        public void writeFloat(float value)
        {
            if (!this.canWrite(sizeof(float)))
            {
                this.extendDeltaCapicity(sizeof(float));
            }

            this.mWriteFloatBytes = System.BitConverter.GetBytes(value);

            if (this.mEndian != SystemEndian.msLocalEndian)
            {
                MArray.Reverse(this.mWriteFloatBytes);
            }

            MArray.Copy(this.mWriteFloatBytes, 0, this.mDynBuffer.getBuffer(), (int)this.mPos, sizeof(float));

            this.advPosAndLen(sizeof(float));
        }

        public void writeDouble(double value)
        {
            if (!this.canWrite(sizeof(double)))
            {
                this.extendDeltaCapicity(sizeof(double));
            }

            this.mWriteDoubleBytes = System.BitConverter.GetBytes(value);

            if(this.mEndian != SystemEndian.msLocalEndian)
            {
                MArray.Reverse(this.mWriteDoubleBytes);
            }

            MArray.Copy(this.mWriteDoubleBytes, 0, this.mDynBuffer.getBuffer(), (int)this.mPos, sizeof(double));

            this.advPosAndLen(sizeof(double));
        }

        // 写入字节， bchangeLen 是否改变长度
        public void writeBytes(byte[] value, uint start, uint len, bool bchangeLen = true)
        {
            if (len > 0)            // 如果有长度才写入
            {
                if (!this.canWrite(len))
                {
                    this.extendDeltaCapicity(len);
                }

                MArray.Copy(value, (int)start, this.mDynBuffer.getBuffer(), (int)this.mPos, (int)len);

                if (bchangeLen)
                {
                    this.advPosAndLen(len);
                }
                else
                {
                    this.advPos(len);
                }
            }
        }

        // 写入字符串
        //public void writeMultiByte(string value, Encoding charSet, int len)
        public void writeMultiByte(string value, MEncode gkCharSet, int len)
        {
            Encoding charSet = UtilSysLibWrap.convOneEncode2AnotherEncode(gkCharSet);
            int num = 0;

            if (null != value)
            {
                //char[] charPtr = value.ToCharArray();
                num = charSet.GetByteCount(value);

                if (0 == len)
                {
                    len = num;
                }

                if (!this.canWrite((uint)len))
                {
                    this.extendDeltaCapicity((uint)len);
                }

                if (num < len)
                {
                    MArray.Copy(charSet.GetBytes(value), 0, this.mDynBuffer.getBuffer(), (int)this.mPos, num);
                    // 后面补齐 0 
                    MArray.Clear(this.mDynBuffer.getBuffer(), (int)(this.mPos + num), len - num);
                }
                else
                {
                    MArray.Copy(charSet.GetBytes(value), 0, this.mDynBuffer.getBuffer(), (int)this.mPos, len);
                }

                this.advPosAndLen((uint)len);
            }
            else
            {
                if (!this.canWrite((uint)len))
                {
                    this.extendDeltaCapicity((uint)len);
                }

                this.advPosAndLen((uint)len);
            }
        }

        // 替换已经有的一段数据
        protected void replace(byte[] srcBytes, uint srcStartPos = 0, uint srclen_ = 0, uint destStartPos = 0, uint destlen_ = 0)
        {
            uint lastLeft = this.getLength() - destStartPos - destlen_;        // 最后一段的长度
            this.setLength(destStartPos + srclen_ + lastLeft);      // 设置大小，保证足够大小空间

            this.setPos(destStartPos + srclen_);
            if (lastLeft > 0)
            {
                this.writeBytes(this.mDynBuffer.getBuffer(), destStartPos + destlen_, lastLeft, false);          // 这个地方自己区域覆盖自己区域，可以保证自己不覆盖自己区域
            }

            this.setPos(destStartPos);
            this.writeBytes(srcBytes, srcStartPos, srclen_, false);
        }

        public void insertUnsignedInt32(uint value)
        {
            this.setLength(this.getLength() + sizeof(int));       // 扩大长度
            this.writeUnsignedInt32(value);     // 写入
        }

        public MByteBuffer readUnsignedLongByOffset(ref ulong tmpUlong, uint offset)
        {
            this.setPos(offset);
            this.readUnsignedInt64(ref tmpUlong);
            return this;
        }

        // 写入 EOF 结束符
        public void end()
        {
            this.mDynBuffer.getBuffer()[this.getLength()] = 0;
        }

        public MByteBuffer readBoolean(ref bool tmpBool)
        {
            if (this.canRead(sizeof(bool)))
            {
                tmpBool = System.BitConverter.ToBoolean(mDynBuffer.getBuffer(), (int)mPos);
                this.advPos(sizeof(bool));
            }

            return this;
        }
    }
}