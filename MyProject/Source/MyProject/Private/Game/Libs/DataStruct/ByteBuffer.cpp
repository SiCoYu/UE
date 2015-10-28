#include "MyProject.h"
#include "ByteBuffer.h"

//#include <sstream>
#include "DynBufResizePolicy.h"
#include "BitConverter.h"
#include "Array.h"

ByteBuffer::ByteBuffer(uint32 initCapacity, uint32 maxCapacity, EEndian endian)
{
	m_endian = endian;        // 缓冲区默认是小端的数据，因为服务器是 linux 的
	m_dynBuff = new DynBuffer<char>(initCapacity, maxCapacity);
}

DynBuffer<char>* ByteBuffer::getDynBuff()
{
	return m_dynBuff;
}

uint32 ByteBuffer::getBytesAvailable()
{
	//check();
	return (m_dynBuff->getSize() - m_pos);
}

EEndian ByteBuffer::getEndian()
{
	return m_endian;
}

void ByteBuffer::setEndian(EEndian value)
{
	m_endian = value;
}

uint32 ByteBuffer::getLength()
{
	return m_dynBuff->getSize();
}

void ByteBuffer::setLength(uint32 value)
{
	m_dynBuff->setSize(value);

	//check();
}

void ByteBuffer::setPos(uint32 pos)
{
	m_pos = pos;

	//check();
}

uint32 ByteBuffer::getPos()
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

void ByteBuffer::clear()
{
	//check();

	m_pos = 0;
	m_dynBuff->setSize(0);
}

// 检查是否有足够的大小可以扩展
bool ByteBuffer::canWrite(uint32 delta)
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
bool ByteBuffer::canRead(uint32 delta)
{
	if (m_pos + delta > m_dynBuff->getSize())
	{
		//check();

		return false;
	}

	//check();

	return true;
}

void ByteBuffer::extendDeltaCapicity(uint32 delta)
{
	m_dynBuff->extendDeltaCapicity(delta);

	//check();
}

void ByteBuffer::advPos(uint32 num)
{
	m_pos += num;

	//check();
}

void ByteBuffer::advPosAndLen(uint32 num)
{
	m_pos += num;
	setLength(m_pos);

	//check();
}

void ByteBuffer::incPosDelta(int delta)        // 添加 pos delta 数量
{
	m_pos += (uint32)delta;
}

void ByteBuffer::decPosDelta(int delta)     // 减少 pos delta 数量
{
	m_pos -= (uint32)delta;
}

void ByteBuffer::incLenDelta(int delta)
{
	setLength(getLength() + (uint32)delta);
}

void ByteBuffer::decLenDelta(int delta)
{
	setLength(getLength() - (uint32)delta);
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

ByteBuffer& ByteBuffer::readInt8(int8& tmpByte)
{
	if (canRead(sizeof(char)))
	{
		tmpByte = (char)BitConverter::ToChar(m_dynBuff->getBuff(), (int)m_pos);
		advPos(sizeof(char));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt8(uint8& tmpByte)
{
	if (canRead(sizeof(uint8)))
	{
		tmpByte = (uint8)BitConverter::ToChar(m_dynBuff->getBuff(), (int)m_pos);
		advPos(sizeof(uint8));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readInt16(int16& tmpShort)
{
	if (canRead(sizeof(int16)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(short));
		}
		tmpShort = BitConverter::ToInt16(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(int16));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt16(uint16& tmpUshort)
{
	if (canRead(sizeof(uint16)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(uint16));
		}
		tmpUshort = BitConverter::ToUInt16(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(uint16));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readInt32(int32& tmpInt)
{
	if (canRead(sizeof(int32)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(int32));
		}
		tmpInt = BitConverter::ToInt32(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(int32));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt32(uint32& tmpUint)
{
	if (canRead(sizeof(uint32)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(uint32));
		}
		tmpUint = BitConverter::ToUInt32(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(uint32));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readInt64(int64& tmpLong)
{
	if (canRead(sizeof(int64)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(int64));
		}
		tmpLong = BitConverter::ToInt64(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(int64));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt64(uint64& tmpUlong)
{
	if (canRead(sizeof(uint64)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(uint64));
		}
		tmpUlong = BitConverter::ToUInt64(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(uint64));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readFloat(float& tmpFloat)
{
	if (canRead(sizeof(float)))
	{
		if (m_endian != SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(float));
		}
		tmpFloat = BitConverter::ToSingle(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(float));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readDouble(double& tmpDouble)
{
	if (canRead(sizeof(double)))
	{
		if (m_endian == SystemEndian::m_sEndian)
		{
			Array::Reverse(m_dynBuff->getBuff(), (int)m_pos, sizeof(double));
		}
		tmpDouble = BitConverter::ToDouble(m_dynBuff->getBuff(), (int)m_pos);

		advPos(sizeof(double));
	}

	//check();

	return *this;
}

ByteBuffer& ByteBuffer::readMultiByte(std::string& tmpStr, uint32 len, MEncode charSet)
{
	// 如果是 unicode ，需要大小端判断
	if (canRead(len))
	{
		//tmpStr = charSet.GetString(m_dynBuff->getBuff(), (int)m_pos, (int)len);
		advPos(len);
	}

	//check();

	return *this;
}

// 这个是字节读取，没有大小端的区别
ByteBuffer& ByteBuffer::readBytes(char* tmpBytes, uint32 len)
{
	if (canRead(len))
	{
		Array::Copy(m_dynBuff->getBuff(), (int)m_pos, tmpBytes, 0, (int)len);
		advPos(len);
	}

	//check();

	return *this;
}

// 如果要使用 writeInt8 ，直接使用 writeMultiByte 这个函数
void ByteBuffer::writeInt8(int8 value)
{
	if (!canWrite(sizeof(int8)))
	{
		extendDeltaCapicity(sizeof(int8));
	}
	m_dynBuff->getBuff()[m_pos] = (int8)value;
	advPosAndLen(sizeof(int8));

	//check();
}

void ByteBuffer::writeUnsignedInt8(uint8 value)
{
	if (!canWrite(sizeof(uint8)))
	{
		extendDeltaCapicity(sizeof(uint8));
	}
	m_dynBuff->getBuff()[m_pos] = value;
	advPosAndLen(sizeof(uint8));

	//check();
}

void ByteBuffer::writeInt16(int16 value)
{
	if (!canWrite(sizeof(int16)))
	{
		extendDeltaCapicity(sizeof(int16));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(int16));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(int16));

	advPosAndLen(sizeof(short));

	//check();
}

void ByteBuffer::writeUnsignedInt16(uint16 value)
{
	if (!canWrite(sizeof(uint16)))
	{
		extendDeltaCapicity(sizeof(uint16));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(uint16));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(uint16));

	advPosAndLen(sizeof(uint16));

	//check();
}

void ByteBuffer::writeInt32(int value)
{
	if (!canWrite(sizeof(int)))
	{
		extendDeltaCapicity(sizeof(int));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(int32));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(int32));

	advPosAndLen(sizeof(int));

	//check();
}

void ByteBuffer::writeUnsignedInt32(uint32 value, bool bchangeLen)
{
	if (!canWrite(sizeof(uint32)))
	{
		extendDeltaCapicity(sizeof(uint32));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(uint32));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(uint32));

	if (bchangeLen)
	{
		advPosAndLen(sizeof(uint32));
	}
	else
	{
		advPos(sizeof(uint32));
	}

	//check();
}

void ByteBuffer::writeInt64(int64 value)
{
	if (!canWrite(sizeof(int64)))
	{
		extendDeltaCapicity(sizeof(int64));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(int64));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(int64));

	advPosAndLen(sizeof(long));

	//check();
}

void ByteBuffer::writeUnsignedInt64(uint64 value)
{
	if (!canWrite(sizeof(uint64)))
	{
		extendDeltaCapicity(sizeof(uint64));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(uint64));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(uint64));

	advPosAndLen(sizeof(uint64));

	//check();
}

void ByteBuffer::writeFloat(float value)
{
	if (!canWrite(sizeof(float)))
	{
		extendDeltaCapicity(sizeof(float));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(float));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(float));

	advPosAndLen(sizeof(float));

	//check();
}

void ByteBuffer::writeDouble(double value)
{
	if (!canWrite(sizeof(double)))
	{
		extendDeltaCapicity(sizeof(double));
	}

	if (m_endian != SystemEndian::m_sEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(double));
	}
	Array::Copy((char*)(&value), 0, m_dynBuff->getBuff(), m_pos, sizeof(double));

	advPosAndLen(sizeof(double));

	//check();
}

// 写入字节， bchangeLen 是否改变长度
void ByteBuffer::writeBytes(char* value, uint32 start, uint32 len, bool bchangeLen)
{
	if (len > 0)            // 如果有长度才写入
	{
		if (!canWrite(len))
		{
			extendDeltaCapicity(len);
		}
		Array::Copy(value, start, m_dynBuff->getBuff(), m_pos, len);
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
void ByteBuffer::writeMultiByte(std::string& value, MEncode charSet, int len)
{
	//int num = 0;

	//if (value.length() > 0)
	//{
	//	//char[] charPtr = value.ToCharArray();
	//	num = charSet.GetByteCount(value);

	//	if (0 == len)
	//	{
	//		len = num;
	//	}

	//	if (!canWrite((uint32)len))
	//	{
	//		extendDeltaCapicity((uint32)len);
	//	}

	//	if (num < len)
	//	{
	//		BufferUtil::Copy(charSet.GetBytes(value), 0, m_dynBuff->getBuff(), m_pos, num);
	//		// 后面补齐 0 
	//		BufferUtil::Clear(m_dynBuff->getBuff(), (int)(m_pos + num), len - num);
	//	}
	//	else
	//	{
	//		BufferUtil::Copy(charSet.GetBytes(value), 0, m_dynBuff->getBuff(), m_pos, len);
	//	}
	//	advPosAndLen((uint32)len);
	//}
	//else
	//{
	//	if (!canWrite((uint32)len))
	//	{
	//		extendDeltaCapicity((uint32)len);
	//	}

	//	advPosAndLen((uint32)len);
	//}

	//check();
}

// 替换已经有的一段数据
void ByteBuffer::replace(char* srcBytes, uint32 srcStartPos, uint32 srclen_, uint32 destStartPos, uint32 destlen_)
{
	uint32 lastLeft = this->getLength() - destStartPos - destlen_;        // 最后一段的长度
	this->setLength(destStartPos + srclen_ + lastLeft);      // 设置大小，保证足够大小空间

	this->setPos(destStartPos + srclen_);
	if (lastLeft > 0)
	{
		writeBytes(m_dynBuff->getBuff(), destStartPos + destlen_, lastLeft, false);          // 这个地方自己区域覆盖自己区域，可以保证自己不覆盖自己区域
	}

	this->setPos(destStartPos);
	writeBytes(srcBytes, srcStartPos, srclen_, false);
	//check();
}

void ByteBuffer::insertUnsignedInt32(uint32 value)
{
	incLenDelta(sizeof(uint32));       // 扩大长度
	writeUnsignedInt32(value);     // 写入
	//check();
}

ByteBuffer& ByteBuffer::readUnsignedLongByOffset(uint64& tmpUlong, uint32 offset)
{
	this->setPos(offset);
	readUnsignedInt64(tmpUlong);
	//check();
	return *this;
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