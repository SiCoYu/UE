#include "MyProject.h"
#include "MByteBuffer.h"

//#include <sstream>
#include "DynBufResizePolicy.h"
#include "BitConverter.h"
#include "Array.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

MByteBuffer::MByteBuffer(
	uint32 initCapacity, 
	uint32 maxCapacity, 
	EEndian endian
)
{
	this->mEndian = endian;        // 缓冲区默认是小端的数据，因为服务器是 linux 的
	this->mDynBuffer = MY_NEW MDynBuffer<char>(
		initCapacity, 
		maxCapacity
		);
	this->mDynBuffer->setPodType(true);
}

MDynBuffer<char>* MByteBuffer::getDynBuffer()
{
	return this->mDynBuffer;
}

uint32 MByteBuffer::getBytesAvailable()
{
	//check();
	return (this->mDynBuffer->getSize() - this->mPos);
}

EEndian MByteBuffer::getEndian()
{
	return this->mEndian;
}

void MByteBuffer::setEndian(EEndian value)
{
	this->mEndian = value;
}

uint32 MByteBuffer::getLength()
{
	return this->mDynBuffer->getSize();
}

void MByteBuffer::setLength(uint32 value)
{
	this->mDynBuffer->setSize(value);

	//check();
}

void MByteBuffer::setPos(uint32 pos)
{
	this->mPos = pos;

	//check();
}

uint32 MByteBuffer::getPos()
{
	return this->mPos;
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

	this->mPos = 0;
	this->mDynBuffer->setSize(0);
}

// 检查是否有足够的大小可以扩展
bool MByteBuffer::canWrite(uint32 delta)
{
	if (this->mDynBuffer->getSize() + delta > this->mDynBuffer->getCapacity())
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
	if (this->mPos + delta > this->mDynBuffer->getSize())
	{
		//check();

		return false;
	}

	//check();

	return true;
}

void MByteBuffer::extendDeltaCapicity(uint32 delta)
{
	this->mDynBuffer->extendDeltaCapicity(delta);

	//check();
}

void MByteBuffer::advPos(uint32 num)
{
	this->mPos += num;

	//check();
}

void MByteBuffer::advPosAndLen(uint32 num)
{
	this->mPos += num;
	setLength(this->mPos);

	//check();
}

void MByteBuffer::incPosDelta(int delta)        // 添加 pos delta 数量
{
	this->mPos += (uint32)delta;
}

void MByteBuffer::decPosDelta(int delta)     // 减少 pos delta 数量
{
	this->mPos -= (uint32)delta;
}

void MByteBuffer::incLenDelta(int delta)
{
	this->setLength(this->getLength() + (uint32)delta);
}

void MByteBuffer::decLenDelta(int delta)
{
	this->setLength(this->getLength() - (uint32)delta);
}

//// 压缩
//uint MByteBuffer::compress(uint len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB)
//{
//	len_ = (len_ == 0 ? length : len_);
//
//	byte[] retByte = nullptr;
//	uint retSize = 0;
//	Compress.CompressData(mDynBuffer.buff, position, len_, ref retByte, ref retSize, algorithm);
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
//	byte[] retByte = nullptr;
//	uint retSize = 0;
//	Compress.DecompressData(mDynBuffer.buff, position, len_, ref retByte, ref retSize, algorithm);
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
//	byte[] retByte = nullptr;
//	// 只有 8 个字节的时候才加密
//	uint leftCnt = len_ % 8;  // 剩余的数量
//	uint cryptCnt = leftCnt;
//
//	if (len_ >= 8)
//	{
//		Crypt.encryptData(mDynBuffer.buff, position, len_ - leftCnt, ref retByte, cryptKey);
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
//		if (m_padBytes == nullptr)
//		{
//			m_padBytes = new byte[8];
//		}
//
//		// 保存数据，然后补 0
//		Array.Copy(mDynBuffer.buff, position + len_, m_padBytes, 0, leftLen_);
//		Array.Clear(mDynBuffer.buff, (int)(position + len_), (int)leftLen_);
//	}
//
//	if (len_ == 0)      // 修正之后还等于 0 
//	{
//		return 0;
//	}
//
//	if (alignLen_ > mDynBuffer.capacity)   // 如果最后加密(由于补齐)的长度大于原始长度
//	{
//		length = alignLen_;
//	}
//
//	byte[] retByte = nullptr;
//
//	Crypt.encryptData(mDynBuffer.buff, position, alignLen_, ref retByte, cryptContext);  // 注意补齐不一定是 0 
//	Array.Copy(m_padBytes, 0, mDynBuffer.buff, position + len_, leftLen_);       // 拷贝回去
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
//	byte[] retByte = nullptr;
//
//	if (0 == len_)
//	{
//		return;
//	}
//
//	Crypt.decryptData(mDynBuffer.buff, position, len_, ref retByte, cryptContext);
//	writeBytes(retByte, 0, (uint)retByte.Length, false);
//
//	//check();
//}
//
//MByteBuffer MByteBuffer::readBoolean(ref bool tmpBool)
//{
//	if (canRead(sizeof(bool)))
//	{
//		tmpBool = System.BitConverter.ToBoolean(mDynBuffer.buff, (int)mPos);
//		advPos(sizeof(bool));
//	}
//
//	//check();
//
//	return this;
//}

MByteBuffer& MByteBuffer::readInt8(int8& tmpByte)
{
	if (this->canRead(sizeof(char)))
	{
		tmpByte = (char)BitConverter::ToChar(this->mDynBuffer->getBuffer(), (int)this->mPos);
		this->advPos(sizeof(char));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readUnsignedInt8(uint8& tmpByte)
{
	if (this->canRead(sizeof(uint8)))
	{
		tmpByte = (uint8)BitConverter::ToChar(this->mDynBuffer->getBuffer(), (int)this->mPos);
		this->advPos(sizeof(uint8));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readInt16(int16& tmpShort)
{
	if (this->canRead(sizeof(int16)))
	{
		if (this->mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(short));
		}
		tmpShort = BitConverter::ToInt16(this->mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(int16));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readUnsignedInt16(uint16& tmpUshort)
{
	if (this->canRead(sizeof(uint16)))
	{
		if (this->mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(uint16));
		}
		tmpUshort = BitConverter::ToUInt16(this->mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(uint16));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readInt32(int32& tmpInt)
{
	if (this->canRead(sizeof(int32)))
	{
		if (this->mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(int32));
		}
		tmpInt = BitConverter::ToInt32(this->mDynBuffer->getBuffer(), (int)this->mPos);

		advPos(sizeof(int32));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readUnsignedInt32(uint32& tmpUint)
{
	if (this->canRead(sizeof(uint32)))
	{
		if (mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(uint32));
		}
		tmpUint = BitConverter::ToUInt32(this->mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(uint32));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readInt64(int64& tmpLong)
{
	if (this->canRead(sizeof(int64)))
	{
		if (this->mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(int64));
		}
		tmpLong = BitConverter::ToInt64(this->mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(int64));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readUnsignedInt64(uint64& tmpUlong)
{
	if (this->canRead(sizeof(uint64)))
	{
		if (this->mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(uint64));
		}

		tmpUlong = BitConverter::ToUInt64(this->mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(uint64));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readFloat(float& tmpFloat)
{
	if (canRead(sizeof(float)))
	{
		if (this->mEndian != SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(float));
		}
		tmpFloat = BitConverter::ToSingle(this->mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(float));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readDouble(double& tmpDouble)
{
	if (canRead(sizeof(double)))
	{
		if (this->mEndian == SystemEndian::msEndian)
		{
			Array::Reverse(this->mDynBuffer->getBuffer(), (int)this->mPos, sizeof(double));
		}
		tmpDouble = BitConverter::ToDouble(mDynBuffer->getBuffer(), (int)this->mPos);

		this->advPos(sizeof(double));
	}

	//check();

	return *this;
}

MByteBuffer& MByteBuffer::readMultiByte(std::string& tmpStr, uint32 len, MEncode charSet)
{
	// 如果是 unicode ，需要大小端判断
	if (this->canRead(len))
	{
		//tmpStr = charSet.GetString(mDynBuffer->getBuffer(), (int)mPos, (int)len);
		this->advPos(len);
	}

	//check();

	return *this;
}

// 这个是字节读取，没有大小端的区别
MByteBuffer& MByteBuffer::readBytes(char* tmpBytes, uint32 len)
{
	if (this->canRead(len))
	{
		Array::Copy(this->mDynBuffer->getBuffer(), (int)this->mPos, tmpBytes, 0, (int)len);
		this->advPos(len);
	}

	//check();

	return *this;
}

// 如果要使用 writeInt8 ，直接使用 writeMultiByte 这个函数
void MByteBuffer::writeInt8(int8 value)
{
	if (!this->canWrite(sizeof(int8)))
	{
		this->extendDeltaCapicity(sizeof(int8));
	}

	this->mDynBuffer->getBuffer()[this->mPos] = (int8)value;
	this->advPosAndLen(sizeof(int8));

	//check();
}

void MByteBuffer::writeUnsignedInt8(uint8 value)
{
	if (!this->canWrite(sizeof(uint8)))
	{
		this->extendDeltaCapicity(sizeof(uint8));
	}

	this->mDynBuffer->getBuffer()[this->mPos] = value;
	this->advPosAndLen(sizeof(uint8));

	//check();
}

void MByteBuffer::writeInt16(int16 value)
{
	if (!this->canWrite(sizeof(int16)))
	{
		this->extendDeltaCapicity(sizeof(int16));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(int16));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(int16));

	this->advPosAndLen(sizeof(short));

	//check();
}

void MByteBuffer::writeUnsignedInt16(uint16 value)
{
	if (!canWrite(sizeof(uint16)))
	{
		extendDeltaCapicity(sizeof(uint16));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(uint16));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(uint16));

	this->advPosAndLen(sizeof(uint16));

	//check();
}

void MByteBuffer::writeInt32(int value)
{
	if (!this->canWrite(sizeof(int)))
	{
		this->extendDeltaCapicity(sizeof(int));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(int32));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(int32));

	this->advPosAndLen(sizeof(int));

	//check();
}

void MByteBuffer::writeUnsignedInt32(uint32 value, bool bchangeLen)
{
	if (!this->canWrite(sizeof(uint32)))
	{
		this->extendDeltaCapicity(sizeof(uint32));
	}

	if (mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(uint32));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(uint32));

	if (bchangeLen)
	{
		this->advPosAndLen(sizeof(uint32));
	}
	else
	{
		this->advPos(sizeof(uint32));
	}

	//check();
}

void MByteBuffer::writeInt64(int64 value)
{
	if (!this->canWrite(sizeof(int64)))
	{
		this->extendDeltaCapicity(sizeof(int64));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(int64));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(int64));

	this->advPosAndLen(sizeof(long));

	//check();
}

void MByteBuffer::writeUnsignedInt64(uint64 value)
{
	if (!this->canWrite(sizeof(uint64)))
	{
		this->extendDeltaCapicity(sizeof(uint64));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(uint64));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(uint64));

	this->advPosAndLen(sizeof(uint64));

	//check();
}

void MByteBuffer::writeFloat(float value)
{
	if (!this->canWrite(sizeof(float)))
	{
		this->extendDeltaCapicity(sizeof(float));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(float));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(float));

	this->advPosAndLen(sizeof(float));

	//check();
}

void MByteBuffer::writeDouble(double value)
{
	if (!this->canWrite(sizeof(double)))
	{
		this->extendDeltaCapicity(sizeof(double));
	}

	if (this->mEndian != SystemEndian::msEndian)
	{
		Array::Reverse((char*)(&value), 0, sizeof(double));
	}
	Array::Copy((char*)(&value), 0, this->mDynBuffer->getBuffer(), this->mPos, sizeof(double));

	this->advPosAndLen(sizeof(double));

	//check();
}

// 写入字节， bchangeLen 是否改变长度
void MByteBuffer::writeBytes(char* value, uint32 start, uint32 len, bool bchangeLen)
{
	if (len > 0)            // 如果有长度才写入
	{
		if (!this->canWrite(len))
		{
			this->extendDeltaCapicity(len);
		}
		Array::Copy(value, start, this->mDynBuffer->getBuffer(), this->mPos, len);
		if (bchangeLen)
		{
			this->advPosAndLen(len);
		}
		else
		{
			this->advPos(len);
		}
	}

	//check();
}

// 写入字符串
void MByteBuffer::writeMultiByte(std::string& value, MEncode charSet, int len)
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
	//		BufferUtil::Copy(charSet.GetBytes(value), 0, mDynBuffer->getBuffer(), mPos, num);
	//		// 后面补齐 0 
	//		BufferUtil::Clear(mDynBuffer->getBuffer(), (int)(mPos + num), len - num);
	//	}
	//	else
	//	{
	//		BufferUtil::Copy(charSet.GetBytes(value), 0, mDynBuffer->getBuffer(), mPos, len);
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
void MByteBuffer::replace(char* srcBytes, uint32 srcStartPos, uint32 srclen_, uint32 destStartPos, uint32 destlen_)
{
	uint32 lastLeft = this->getLength() - destStartPos - destlen_;        // 最后一段的长度
	this->setLength(destStartPos + srclen_ + lastLeft);      // 设置大小，保证足够大小空间

	this->setPos(destStartPos + srclen_);
	if (lastLeft > 0)
	{
		this->writeBytes(mDynBuffer->getBuffer(), destStartPos + destlen_, lastLeft, false);          // 这个地方自己区域覆盖自己区域，可以保证自己不覆盖自己区域
	}

	this->setPos(destStartPos);
	this->writeBytes(srcBytes, srcStartPos, srclen_, false);
	//check();
}

void MByteBuffer::insertUnsignedInt32(uint32 value)
{
	this->incLenDelta(sizeof(uint32));       // 扩大长度
	this->writeUnsignedInt32(value);     // 写入
	//check();
}

MByteBuffer& MByteBuffer::readUnsignedLongByOffset(uint64& tmpUlong, uint32 offset)
{
	this->setPos(offset);
	this->readUnsignedInt64(tmpUlong);
	//check();
	return *this;
}

//bool MByteBuffer::check()
//{
//    if (m_startTest && mId == 1000)
//    {
//        if (mPos == 32 || mPos == 16)
//        {
//            if (length == 32 || length == 16)
//            {
//                return false;
//            }
//        }
//    }

//    if (mDynBuffer.size < mPos)
//    {
//        return false;
//    }

//    return true;
//}

MY_END_NAMESPACE