#include "MyProject.h"
#include "MByteBuffer.h"

#include <sstream>
#include "DynBufResizePolicy.h"

MByteBuffer::MByteBuffer(uint32 initCapacity, uint32 maxCapacity, SysEndian endian)
{
	m_endian = endian;        // 缓冲区默认是小端的数据，因为服务器是 linux 的
	m_dynBuff = new DynBuffer<char>*(initCapacity, maxCapacity);
}

DynBuffer<char>* MByteBuffer::getDynBuff()
{
	return m_dynBuff;
}

uint32 MByteBuffer::getBytesAvailable()
{
	//check();
	return (m_dynBuff->getSize() - m_pos);
}

SysEndian MByteBuffer::getEndian()
{
	return m_endian;
}

void MByteBuffer::setEndian(SysEndian value)
{
	m_endian = value;
}

uint32 MByteBuffer::getLength()
{
	return m_dynBuff->getSize();
}

void MByteBuffer::setLength(uint32 value)
{
	m_dynBuff->setSize(value);

	//check();
}

void MByteBuffer::setPos(uint32 pos)
{
	m_pos = pos;

	//check();
}

uint32 MByteBuffer::getPos()
{
	return m_pos;
}

//LuaCSBridgeByteBuffer* MByteBuffer::getLuaCSBridgeByteBuffer()
//{
//	return m_luaCSBridgeByteBuffer;
//}
//
//void MByteBuffer::setLuaCSBridgeByteBuffer(LuaCSBridgeByteBuffer* value)
//{
//	m_luaCSBridgeByteBuffer = value;
//}

void MByteBuffer::clear()
{
	//check();

	m_pos = 0;
	m_dynBuff->setSize(0);
}

// 检查是否有足够的大小可以扩展
bool MByteBuffer::canWrite(uint32 delta)
{
	if (m_dynBuff->getSize() + delta > m_dynBuff->getCapacity())
	{
		//check();

		return false;
	}

	//check();

	return true;
}

// 读取检查
bool MByteBuffer::canRead(uint32 delta)
{
	if (m_pos + delta > m_dynBuff->getSize())
	{
		//check();

		return false;
	}

	//check();

	return true;
}

void MByteBuffer::extendDeltaCapicity(uint32 delta)
{
	m_dynBuff->extendDeltaCapicity(delta);

	//check();
}

void MByteBuffer::advPos(uint32 num)
{
	m_pos += num;

	//check();
}

void MByteBuffer::advPosAndLen(uint32 num)
{
	m_pos += num;
	setLength(m_pos);

	//check();
}

void MByteBuffer::incPosDelta(int delta)        // 添加 pos delta 数量
{
	m_pos += (uint32)delta;
}

void MByteBuffer::decPosDelta(int delta)     // 减少 pos delta 数量
{
	m_pos -= (uint32)delta;
}

//// 压缩
//uint MByteBuffer::compress(uint len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB)
//{
//	len_ = (len_ == 0 ? length : len_);
//
//	byte[] retByte = null;
//	uint retSize = 0;
//	Compress.CompressData(m_dynBuff.buff, position, len_, ref retByte, ref retSize, algorithm);
//
//	replace(retByte, 0, retSize, position, len_);
//
//	//check();
//
//	return retSize;
//}
//
//// 解压
//uint MByteBuffer::uncompress(uint len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB)
//{
//	len_ = (len_ == 0 ? length : len_);
//
//	byte[] retByte = null;
//	uint retSize = 0;
//	Compress.DecompressData(m_dynBuff.buff, position, len_, ref retByte, ref retSize, algorithm);
//
//	replace(retByte, 0, retSize, position, len_);
//
//	//check();
//
//	return retSize;
//}
//
//// 加密，使用 des 对称数字加密算法，加密8字节补齐，可能会导致变长
//uint MByteBuffer::encrypt(CryptContext cryptContext, uint len_ = 0)
//{
//#if OBSOLETE
//	len_ = (len_ == 0 ? length : len_);
//
//	byte[] retByte = null;
//	// 只有 8 个字节的时候才加密
//	uint leftCnt = len_ % 8;  // 剩余的数量
//	uint cryptCnt = leftCnt;
//
//	if (len_ >= 8)
//	{
//		Crypt.encryptData(m_dynBuff.buff, position, len_ - leftCnt, ref retByte, cryptKey);
//		writeBytes(retByte, 0, (uint)retByte.Length, false);
//		cryptCnt += (uint)retByte.Length;
//	}
//
//	if (leftCnt > 0) // 如果还有剩余的字节没有加密，还需要增加长度
//	{
//		position += leftCnt;
//	}
//
//	return cryptCnt;
//#endif
//	len_ = (len_ == 0 ? length : len_);
//	uint alignLen_ = ((len_ + 7) / 8) * 8; // 补齐 8 个字节，因为加密是 8 个字节一次加密，只要是 8 个字节的整数倍，无论多少个都可以任意解压
//	uint leftLen_ = alignLen_ - len_;
//	if (leftLen_ > 0)
//	{
//		if (m_padBytes == null)
//		{
//			m_padBytes = new byte[8];
//		}
//
//		// 保存数据，然后补 0
//		Array.Copy(m_dynBuff.buff, position + len_, m_padBytes, 0, leftLen_);
//		Array.Clear(m_dynBuff.buff, (int)(position + len_), (int)leftLen_);
//	}
//
//	if (len_ == 0)      // 修正之后还等于 0 
//	{
//		return 0;
//	}
//
//	if (alignLen_ > m_dynBuff.capacity)   // 如果最后加密(由于补齐)的长度大于原始长度
//	{
//		length = alignLen_;
//	}
//
//	byte[] retByte = null;
//
//	Crypt.encryptData(m_dynBuff.buff, position, alignLen_, ref retByte, cryptContext);  // 注意补齐不一定是 0 
//	Array.Copy(m_padBytes, 0, m_dynBuff.buff, position + len_, leftLen_);       // 拷贝回去
//	replace(retByte, 0, alignLen_, position, len_);
//
//	//check();
//
//	return alignLen_;
//}
//
//// 解密，现在必须 8 字节对齐解密
//void MByteBuffer::decrypt(CryptContext cryptContext, uint len_ = 0)
//{
//	len_ = (len_ == 0 ? length : len_);
//
//	byte[] retByte = null;
//
//	if (0 == len_)
//	{
//		return;
//	}
//
//	Crypt.decryptData(m_dynBuff.buff, position, len_, ref retByte, cryptContext);
//	writeBytes(retByte, 0, (uint)retByte.Length, false);
//
//	//check();
//}
//
//ByteBuffer MByteBuffer::readBoolean(ref bool tmpBool)
//{
//	if (canRead(sizeof(bool)))
//	{
//		tmpBool = System.BitConverter.ToBoolean(m_dynBuff.buff, (int)m_pos);
//		advPos(sizeof(bool));
//	}
//
//	//check();
//
//	return this;
//}

MByteBuffer& MByteBuffer::readInt8(char& tmpByte)
{
	if (canRead(sizeof(char)))
	{
		tmpByte = (char)System.BitConverter.ToChar(m_dynBuff->getBuff()uff, (int)m_pos);
		advPos(sizeof(char));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readUnsignedInt8(uint8& tmpByte)
{
	if (canRead(sizeof(uint8)))
	{
		tmpByte = (byte)System.BitConverter.ToChar(m_dynBuff.buff, (int)m_pos);
		advPos(sizeof(byte));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readInt16(int16 tmpShort)
{
	if (canRead(sizeof(int16)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpShort = System.BitConverter.ToInt16(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_shortByte, 0, sizeof(short));
			//Array.Reverse(m_shortByte);
			//tmpShort = System.BitConverter.ToInt16(m_shortByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(short));
			System.BitConverter.ToInt16(m_dynBuff.buff, (int)m_pos);
		}

		advPos(sizeof(int16));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readUnsignedInt16(ref ushort tmpUshort)
{
	if (canRead(sizeof(ushort)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpUshort = System.BitConverter.ToUInt16(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_shortByte, 0, sizeof(ushort));
			//Array.Reverse(m_shortByte);
			//tmpUshort = System.BitConverter.ToUInt16(m_shortByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(ushort));
			System.BitConverter.ToUInt16(m_dynBuff.buff, (int)m_pos);
		}

		advPos(sizeof(ushort));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readInt32(ref int tmpInt)
{
	if (canRead(sizeof(int)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpInt = System.BitConverter.ToInt32(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_intByte, 0, sizeof(int));
			//Array.Reverse(m_intByte);
			//tmpInt = System.BitConverter.ToInt32(m_intByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(int));
			System.BitConverter.ToInt32(m_dynBuff.buff, (int)m_pos);
		}
		advPos(sizeof(int));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readUnsignedInt32(ref uint tmpUint)
{
	if (canRead(sizeof(uint)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpUint = System.BitConverter.ToUInt32(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_intByte, 0, sizeof(uint));
			//Array.Reverse(m_intByte);
			//tmpUint = System.BitConverter.ToUInt32(m_intByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(uint));
			System.BitConverter.ToUInt32(m_dynBuff.buff, (int)m_pos);
		}

		advPos(sizeof(uint));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readInt64(ref long tmpLong)
{
	if (canRead(sizeof(long)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpLong = System.BitConverter.ToInt64(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_longByte, 0, sizeof(long));
			//Array.Reverse(m_longByte);
			//tmpLong = System.BitConverter.ToInt64(m_longByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(long));
			System.BitConverter.ToInt64(m_dynBuff.buff, (int)m_pos);
		}

		advPos(sizeof(long));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readUnsignedInt64(ref ulong tmpUlong)
{
	if (canRead(sizeof(ulong)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpUlong = System.BitConverter.ToUInt64(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_longByte, 0, sizeof(ulong));
			//Array.Reverse(m_longByte);
			//tmpUlong = System.BitConverter.ToUInt64(m_longByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(ulong));
			System.BitConverter.ToUInt64(m_dynBuff.buff, (int)m_pos);
		}

		advPos(sizeof(ulong));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readFloat(ref float tmpFloat)
{
	if (canRead(sizeof(float)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpFloat = System.BitConverter.ToSingle(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_floatByte, 0, sizeof(float));
			//Array.Reverse(m_floatByte);
			//tmpFloat = System.BitConverter.ToSingle(m_floatByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(float));
			System.BitConverter.ToSingle(m_dynBuff.buff, (int)m_pos);
		}
		advPos(sizeof(float));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readDouble(ref double tmpDouble)
{
	if (canRead(sizeof(double)))
	{
		if (m_endian == SystemEndian.m_sEndian)
		{
			tmpDouble = System.BitConverter.ToDouble(m_dynBuff.buff, (int)m_pos);
		}
		else
		{
			//Array.Copy(m_dynBuff.buff, (int)m_pos, m_doubleByte, 0, sizeof(double));
			//Array.Reverse(m_doubleByte);
			//tmpDouble = System.BitConverter.ToDouble(m_doubleByte, 0);
			Array.Reverse(m_dynBuff.buff, (int)m_pos, sizeof(double));
			System.BitConverter.ToDouble(m_dynBuff.buff, (int)m_pos);
		}
		advPos(sizeof(double));
	}

	//check();

	return this;
}

MByteBuffer& MByteBuffer::readMultiByte(ref string tmpStr, uint len, Encoding charSet)
{
	// 如果是 unicode ，需要大小端判断
	if (canRead(len))
	{
		tmpStr = charSet.GetString(m_dynBuff.buff, (int)m_pos, (int)len);
		advPos(len);
	}

	//check();

	return this;
}

// 这个是字节读取，没有大小端的区别
MByteBuffer& MByteBuffer::readBytes(ref byte[] tmpBytes, uint len)
{
	if (canRead(len))
	{
		Array.Copy(m_dynBuff.buff, (int)m_pos, tmpBytes, 0, (int)len);
		advPos(len);
	}

	//check();

	return this;
}

// 如果要使用 writeInt8 ，直接使用 writeMultiByte 这个函数
void MByteBuffer::writeInt8(char value)
{
	if (!canWrite(sizeof(char)))
	{
		extendDeltaCapicity(sizeof(char));
	}
	m_dynBuff.buff[m_pos] = (byte)value;
	advPosAndLen(sizeof(char));

	//check();
}

void writeUnsignedInt8(byte value)
{
	if (!canWrite(sizeof(byte)))
	{
		extendDeltaCapicity(sizeof(byte));
	}
	m_dynBuff.buff[m_pos] = value;
	advPosAndLen(sizeof(byte));

	//check();
}

void MByteBuffer::writeInt16(short value)
{
	if (!canWrite(sizeof(short)))
	{
		extendDeltaCapicity(sizeof(short));
	}

	m_writeInt16Bytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeInt16Bytes);
	}
	Array.Copy(m_writeInt16Bytes, 0, m_dynBuff.buff, m_pos, sizeof(short));

	advPosAndLen(sizeof(short));

	//check();
}

void MByteBuffer::writeUnsignedInt16(ushort value)
{
	if (!canWrite(sizeof(ushort)))
	{
		extendDeltaCapicity(sizeof(ushort));
	}

	m_writeInt16Bytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeInt16Bytes);
	}
	Array.Copy(m_writeInt16Bytes, 0, m_dynBuff.buff, m_pos, sizeof(ushort));

	advPosAndLen(sizeof(ushort));

	//check();
}

void MByteBuffer::writeInt32(int value)
{
	if (!canWrite(sizeof(int)))
	{
		extendDeltaCapicity(sizeof(int));
	}

	m_writeInt32Bytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeInt32Bytes);
	}
	Array.Copy(m_writeInt32Bytes, 0, m_dynBuff.buff, m_pos, sizeof(int));

	advPosAndLen(sizeof(int));

	//check();
}

void MByteBuffer::writeUnsignedInt32(uint value, bool bchangeLen = true)
{
	if (!canWrite(sizeof(uint)))
	{
		extendDeltaCapicity(sizeof(uint));
	}

	m_writeInt32Bytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeInt32Bytes);
	}
	Array.Copy(m_writeInt32Bytes, 0, m_dynBuff.buff, m_pos, sizeof(uint));

	if (bchangeLen)
	{
		advPosAndLen(sizeof(uint));
	}
	else
	{
		advPos(sizeof(uint));
	}

	//check();
}

void MByteBuffer::writeInt64(long value)
{
	if (!canWrite(sizeof(long)))
	{
		extendDeltaCapicity(sizeof(long));
	}

	m_writeInt64Bytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeInt64Bytes);
	}
	Array.Copy(m_writeInt64Bytes, 0, m_dynBuff.buff, m_pos, sizeof(long));

	advPosAndLen(sizeof(long));

	//check();
}

void MByteBuffer::writeUnsignedInt64(ulong value)
{
	if (!canWrite(sizeof(ulong)))
	{
		extendDeltaCapicity(sizeof(ulong));
	}

	m_writeInt64Bytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeInt64Bytes);
	}
	Array.Copy(m_writeInt64Bytes, 0, m_dynBuff.buff, m_pos, sizeof(ulong));

	advPosAndLen(sizeof(ulong));

	//check();
}

void MByteBuffer::writeFloat(float value)
{
	if (!canWrite(sizeof(float)))
	{
		extendDeltaCapicity(sizeof(float));
	}

	m_writeFloatBytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeFloatBytes);
	}
	Array.Copy(m_writeFloatBytes, 0, m_dynBuff.buff, m_pos, sizeof(float));

	advPosAndLen(sizeof(float));

	//check();
}

void MByteBuffer::writeDouble(double value)
{
	if (!canWrite(sizeof(double)))
	{
		extendDeltaCapicity(sizeof(double));
	}

	m_writeDoubleBytes = System.BitConverter.GetBytes(value);
	if (m_endian != SystemEndian.m_sEndian)
	{
		Array.Reverse(m_writeDoubleBytes);
	}
	Array.Copy(m_writeDoubleBytes, 0, m_dynBuff.buff, m_pos, sizeof(double));

	advPosAndLen(sizeof(double));

	//check();
}

// 写入字节， bchangeLen 是否改变长度
void MByteBuffer::writeBytes(byte[] value, uint start, uint len, bool bchangeLen = true)
{
	if (len > 0)            // 如果有长度才写入
	{
		if (!canWrite(len))
		{
			extendDeltaCapicity(len);
		}
		Array.Copy(value, start, m_dynBuff.buff, m_pos, len);
		if (bchangeLen)
		{
			advPosAndLen(len);
		}
		else
		{
			advPos(len);
		}
	}

	//check();
}

// 写入字符串
void MByteBuffer::writeMultiByte(string value, Encoding charSet, int len)
{
	int num = 0;

	if (null != value)
	{
		//char[] charPtr = value.ToCharArray();
		num = charSet.GetByteCount(value);

		if (0 == len)
		{
			len = num;
		}

		if (!canWrite((uint)len))
		{
			extendDeltaCapicity((uint)len);
		}

		if (num < len)
		{
			Array.Copy(charSet.GetBytes(value), 0, m_dynBuff.buff, m_pos, num);
			// 后面补齐 0 
			Array.Clear(m_dynBuff.buff, (int)(m_pos + num), len - num);
		}
		else
		{
			Array.Copy(charSet.GetBytes(value), 0, m_dynBuff.buff, m_pos, len);
		}
		advPosAndLen((uint)len);
	}
	else
	{
		if (!canWrite((uint)len))
		{
			extendDeltaCapicity((uint)len);
		}

		advPosAndLen((uint)len);
	}

	//check();
}

// 替换已经有的一段数据
void MByteBuffer::replace(byte[] srcBytes, uint srcStartPos = 0, uint srclen_ = 0, uint destStartPos = 0, uint destlen_ = 0)
{
	uint lastLeft = length - destStartPos - destlen_;        // 最后一段的长度
	length = destStartPos + srclen_ + lastLeft;      // 设置大小，保证足够大小空间

	position = destStartPos + srclen_;
	if (lastLeft > 0)
	{
		writeBytes(m_dynBuff.buff, destStartPos + destlen_, lastLeft, false);          // 这个地方自己区域覆盖自己区域，可以保证自己不覆盖自己区域
	}

	position = destStartPos;
	writeBytes(srcBytes, srcStartPos, srclen_, false);
	//check();
}

void MByteBuffer::insertUnsignedInt32(uint value)
{
	length += sizeof(int);       // 扩大长度
	writeUnsignedInt32(value);     // 写入
	//check();
}

ByteBuffer MByteBuffer::readUnsignedLongByOffset(ref ulong tmpUlong, uint offset)
{
	position = offset;
	readUnsignedInt64(ref tmpUlong);
	//check();
	return this;
}

//bool MByteBuffer::check()
//{
//    if (m_startTest && m_id == 1000)
//    {
//        if (m_pos == 32 || m_pos == 16)
//        {
//            if (length == 32 || length == 16)
//            {
//                return false;
//            }
//        }
//    }

//    if (m_dynBuff.size < m_pos)
//    {
//        return false;
//    }

//    return true;
//}